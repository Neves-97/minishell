/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:39 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:14:40 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	setup_pipe_bools(t_io *io)
{
	if (!io)
		return ;
	if (io->cmd_type == SINGLE_CMD)
	{
		io->use_pipe[READ] = FALSE;
		io->use_pipe[WRITE] = FALSE;
	}
	else if (io->cmd_type == FIRST_CMD)
	{
		io->use_pipe[READ] = FALSE;
		io->use_pipe[WRITE] = TRUE;
	}
	else if (io->cmd_type == MIDDLE_CMD)
	{
		io->use_pipe[READ] = TRUE;
		io->use_pipe[WRITE] = TRUE;
	}
	else if (io->cmd_type == LAST_CMD)
	{
		io->use_pipe[READ] = TRUE;
		io->use_pipe[WRITE] = FALSE;
	}
}

void	execute_pipe(t_ast *root)
{
	int	pipe_fd[2];
	int	tmp[2];

	if (pipe(pipe_fd) == -1)
		exit(1);
	tmp[READ] = pipe_fd[READ];
	tmp[WRITE] = pipe_fd[WRITE];
	handle_command(root->left, setup_io(FIRST_CMD, pipe_fd, tmp[READ]));
	root = root->right;
	while (root && root->type == AST_PIPE)
	{
		close(tmp[WRITE]);
		if (pipe(pipe_fd) == -1)
			exit(1);
		tmp[WRITE] = pipe_fd[WRITE];
		handle_command(root->left, setup_io(MIDDLE_CMD, pipe_fd, tmp[READ]));
		close(tmp[READ]);
		tmp[READ] = pipe_fd[READ];
		root = root->right;
	}
	tmp[READ] = pipe_fd[READ];
	handle_command(root, setup_io(LAST_CMD, pipe_fd, tmp[READ]));
	close(tmp[READ]);
	close(tmp[WRITE]);
}
