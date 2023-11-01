#include "../../includes/minishell.h"

// void free_cmd(t_cmd *cmd)
// {
//     int i = 0;
    
//     if (cmd->cmds)
//     {
//         while (i < cmd->num_cmds)
//         {
//             if (cmd->cmds[i])
//             {
//                 free(cmd->cmds[i]);
//                 cmd->cmds[i] = NULL;
//             }
//             i++;
//         }
//         free(cmd->cmds);
//         cmd->cmds = NULL;
//     }
//     if (cmd->io)
//     {
//         free(cmd->io);
//         cmd->io = NULL;
//     }
// }

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmds)
	{
		while (i < cmd->num_cmds)
		{
			if (cmd->cmds[i])
				free(cmd->cmds[i]);
			i++;
		}
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
		return ;
	if (root->type == AST_CMD)
	{
		setup_cmd(root, io, &cmd);
		exec_cmd(&cmd);
		// free_cmd(&cmd);
	}
}
