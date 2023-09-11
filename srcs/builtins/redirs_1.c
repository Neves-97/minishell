#include "../../includes/minishell.h"

int out_tr_redir(t_ast *node, int *out_fd) {
    if (*out_fd != -1)
        close(*out_fd);
    *out_fd = open(node->content, O_CREAT | O_TRUNC | O_WRONLY, 0664);
    if (*out_fd == -1)
        exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
    return 0;
}

int out_ap_redir(t_ast *node, int *out_fd) {
    if (*out_fd != -1)
        close(*out_fd);
    *out_fd = open(node->content, O_CREAT | O_APPEND | O_WRONLY, 0664);
    if (*out_fd == -1)
        exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
    return 0;
}

int in_redir(t_ast *node, int *in_fd) {
    if (*in_fd != -1)
        close(*in_fd);
    *in_fd = open(node->content, O_RDONLY, 0664);
    if (*in_fd == -1)
        exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
    return 0;
}

int setup_redir_cases(t_ast *node, int *in_fd, int *out_fd) 
{
    if (node->type == NODE_RED_OTR)
        return (out_tr_redir(node, out_fd));
    else if (node->type == NODE_RED_OAP)
        return (out_ap_redir(node, out_fd));
    else if (node->type == NODE_RED_IN)
        return (in_redir(node, in_fd));
    return -1;
}

int setup_file_redir(t_cmd *cmd, t_bool is_parent) {
    t_ast   *tmp;
    int     in_fd;
    int     out_fd;

    tmp = cmd->io->redirection;
    in_fd = -1;
    out_fd = -1;
    while (tmp) {
        if (setup_redir_cases(tmp, &in_fd, &out_fd))
            return 1;
        tmp = tmp->left;
    }
    if (in_fd != -1 && !is_parent) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }
    if (out_fd != -1) {
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
    return 0;
}