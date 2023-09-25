#include "../../includes/minishell.h"

void    handle_command(t_ast *root, t_io *io) {
    t_cmd   cmd;

    if (!root || !io)
        return ;
    if (root->type == NODE_COMMAND) {
        setup_cmd(root, io, &cmd);
        exec_cmd(&cmd);
    }
}
