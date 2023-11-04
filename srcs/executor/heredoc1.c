#include "../../includes/minishell.h"

void	here_run(char *eof, int fd)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (ft_strlen(input) == ft_strlen(eof))
		{
			if (!ft_strncmp(eof, input, ft_strlen(eof)))
			{
				close(fd);
				free(input);
				exit(EXIT_SUCCESS);
			}
		}
		ft_putendl_fd(input, fd);
		free(input);
	}
	ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
	close(fd);
	free(input);
	exit(EXIT_SUCCESS);
}

int	hd_input(char *eof, int fd)
{
	pid_t	pid;
	int		wstatus;

	pid = fork();
	if (pid == -1)
	{
		// free_tokens_ast();
		// free_ptp(get()->env);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		heredoc_signals();
		here_run(eof, fd);
	}
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

	fd = open(".heredoc", O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		exit(EXIT_FAILURE);
	if (!hd_input(redir->content, fd))
	{
		close(fd);
		return (0);
	}
	free(redir->content);
	redir->content = ft_strdup(".heredoc");
	// free_tokens_ast();
	// free_ptp(get()->env);
	close(fd);
	return (1);
}

int	hd_command(t_ast *root)
{
	t_ast	*redirection;

	redirection = root->left;
	while (redirection)
	{
		if (redirection->type == AST_RDI_HD)
		{
			if (!handle_hd(redirection))
				return (0);
		}
		redirection = redirection->left;
	}
	return (1);
}

/* Execute the <pipe> syntax block */
int	hd_pipe(t_ast *root)
{
	t_ast	*job;

	if (!hd_command(root->left))
		return (0);
	job = root->right;
	while (job && job->type == AST_PIPE)
	{
		if (!hd_command(job->left))
			return (0);
		job = job->right;
	}
	if (!hd_command(job))
		return (0);
	return (1);
}
