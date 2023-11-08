/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:29 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:14:30 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_commands(t_cmd *cmd)
{
	if (cmd->cmds)
	{
		free(cmd->cmds);
		cmd->cmds = NULL;
	}
	if (cmd->io)
	{
		free(cmd->io);
		cmd->io = NULL;
	}
}

void	handle_command(t_ast *root, t_io *io)
{
	t_cmd	cmd;

	if (!root || !io)
	{
		return ;
	}
	if (root->type == AST_CMD)
	{
		setup_cmd(root, io, &cmd);
		exec_cmd(&cmd);
		free(cmd.cmds);
		free(cmd.io);
	}
	else
		free(io);
}
