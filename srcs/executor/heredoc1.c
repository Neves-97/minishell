/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:31 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 17:19:35 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	here_run(char *eof, int fd)
{
	char	*input;
	char	*tmp;

	pqp()[0] = 1;
	while (1)
	{
		input = readline("> ");
		if (!input)
			break ;
		if (ft_strlen(input) == ft_strlen(eof))
		{
			if (!ft_strncmp(eof, input, ft_strlen(eof)))
			{
				hd_free(&fd, input);
				exit(EXIT_SUCCESS);
			}
		}
		tmp = input;
		input = handle_quotes(tmp);
		free (tmp);
		ft_putendl_fd(input, fd);
		free(input);
	}
	hd_free(&fd, input);
	exit(EXIT_SUCCESS);
}

void	child_here(char *eof, int fd)
{
	here_run(eof, fd);
	pqp()[0] = 0;
	exit(0);
}

int	hd_input(char *eof, int fd)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		free_them_all();
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_here(eof, fd);
	else
	{
		ignore_signals();
		waitpid(pid, &wstatus, 0);
		if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) + 128 == 130)
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			return (0);
		}
		parent_signals();
	}
	return (1);
}

int	handle_hd(t_ast *redir)
{
	int	fd;

	fd = open(".here", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (!hd_input(redir->content, fd))
	{
		close(fd);
		return (0);
	}
	free(redir->content);
	redir->content = ft_strdup(".here");
	close(fd);
	return (1);
}

int	hd_command(t_ast *root)
{
	t_ast	*redirection;

	if (root->left && root->type == 0) // second condition might be useless or wrong
		redirection = root->left;
	else
		redirection = root;
	while (redirection)
	{
		if (redirection->type == AST_RDI_HD)
		{
			if (!handle_hd(redirection))
			{
				return (0);
			}
		}
		redirection = redirection->left;
	}
	return (1);
}
