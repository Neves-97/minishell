/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:36 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:14:37 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_job(t_ast *root)
{
	int	pipe_fd[2];

	pipe_fd[READ] = -1;
	pipe_fd[WRITE] = -1;
	if (!root)
		return ;
	if (root->type == AST_PIPE)
		execute_pipe(root);
	else
		handle_command(root, setup_io(SINGLE_CMD, pipe_fd, 0));
	wait_exec();
}
