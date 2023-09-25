#include "../../includes/minishell.h"

t_io    *setup_io(int io_type, int pipe_fd[2], int read_fd) {
    t_io *io;

    io = malloc(sizeof(t_io));
    if (!io)
        return (NULL);
    io->cmd_type = io_type;

    // Setting up use_pipe[2]
    setup_pipe_bools(io);
    if (io_type != SINGLE_CMD) {
        io->pipe_fd[READ] = pipe_fd[READ];
        io->pipe_fd[WRITE] = pipe_fd[WRITE];
        io->read_fd = read_fd;
    }
    io->redirection = NULL;
    return io;
}

char **create_args(t_ast *root, t_cmd *cmd) {
    t_ast   *tmp;
    char    **arr;
    int     i;

    arr = calloc(cmd->num_cmds + 1, sizeof(char *));
    if (!arr)
        return (NULL);
    tmp = root;
    i = 0;
    while (tmp) {
        arr[i] = tmp->content;
        tmp = tmp->right;
        i++;
    }
    arr[i] = NULL;
    return (arr);
}

void    setup_cmd(t_ast *root, t_io *io, t_cmd *cmd) {
    cmd->io = io;
    cmd->io->redirection = root->left;
    cmd->num_cmds = count_cmds(root);
    if (!root->content) {
        cmd->cmds = NULL;
        return ;
    }
    cmd->cmds = create_args(root, cmd);
}

int setup_redir(t_cmd *cmd, t_bool is_parent) {
    if (setup_file_redir(cmd, is_parent))
        return (1);
    return 0;
}
