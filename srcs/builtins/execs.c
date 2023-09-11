#include "../../includes/minishell.h"

void    execute_pipe(t_ast *root)
{
    int pipe_fd[2];
    int tmp[2];

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

void    execute_job(t_ast *root) {
    int pipe_fd[2];
    pipe_fd[READ] = -1;
    pipe_fd[WRITE] = -1;
    if (!root)
        return ;
    if (root->type == NODE_PIPE)
        execute_pipe(root);   //TODO: Call execute_pipe function
    else
        handle_command(root, setup_io(SINGLE_CMD, pipe_fd, 0));
    // wait_exec();
}

void exec_ast(t_ast *root)
{
    if (root == NULL)
        return;
    if (root->type == NODE_COMMAND)
        printf("command: %s\n", root->content);
    else if (root->type == NODE_ARGUMENT)
        printf("arg: %s\n", root->content);
    else if (root->type == NODE_RED_IN)
        printf("redirect in: %s\n", root->content);
    else if (root->type == NODE_RED_OAP)
        printf("redirect apend: %s\n", root->content);
    else if (root->type == NODE_RED_OTR)
        printf("redirect subs: %s\n", root->content);
    else if (root->type == NODE_RED_HD)
        printf("redirect heredoc: %s\n", root->content);
    exec_ast(root->left);
    exec_ast(root->right);
}

void exec_cmd(t_cmd *cmd) {
    if (!cmd->cmds)
        exit(1);    // TODO: Handle because there was an error, and exit
    handle_normal_cmd(cmd);
}