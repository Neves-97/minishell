#include "../../includes/minishell.h"

char **environment;

void    setup_pipe_bools(t_io *io) {
    if (!io)
        return ;
    if (io->cmd_type == SINGLE_CMD) {
        io->use_pipe[READ] = FALSE;
        io->use_pipe[WRITE] = FALSE;
    } else if (io->cmd_type == FIRST_CMD) {
        io->use_pipe[READ] = FALSE;
        io->use_pipe[WRITE] = TRUE;
    } else if (io->cmd_type == MIDDLE_CMD) {
        io->use_pipe[READ] = TRUE;
        io->use_pipe[WRITE] = TRUE;
    } else if (io->cmd_type == LAST_CMD) {
        io->use_pipe[READ] = TRUE;
        io->use_pipe[WRITE] = FALSE;
    }
}

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

t_ast *new_node(const char *data, int type)
{
    t_ast *node = (t_ast *)malloc(sizeof(t_ast));
    if (node != NULL)
    {
        node->content = strdup(data);
        node->type = type;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

t_ast *insert(t_ast *root, const char *data, int type)
{
    if (root == NULL)
        return new_node(data, type);
    int comparison = strcmp(data, root->content);
    if (comparison < 0)
        root->left = insert(root->left, data, type);
    else if (comparison > 0)
        root->right = insert(root->right, data, type);
    return root;
}

int count_cmds(t_ast *root) {
    t_ast   *tmp;
    int     counter;

    if (!root)
        return 0;
    if (root->type != NODE_COMMAND)
        return 0;
    tmp = root;
    counter = 0;
    while (tmp) {
        counter++;
        tmp = tmp->right;
    }
    return counter;
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

void print_array(char **arr) {
    if (!arr || !*arr)
        return ;
    int i = 0;
    printf("[ ");
    while (arr[i]) {
        printf("%s", arr[i]);
        i++;
        if (arr[i])
            printf(", ");
    }
    printf(" ]\n");
}

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

int setup_redir_cases(t_ast *node, int *in_fd, int *out_fd) {
    if (node->type == NODE_RED_OTR)
        return (out_tr_redir(node, out_fd));
    else if (node->type == NODE_RED_OAP)
        return (out_ap_redir(node, out_fd));
    else if (node->type == NODE_RED_IN)
        return (in_redir(node, in_fd));
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

int setup_redir(t_cmd *cmd, t_bool is_parent) {
    if (setup_file_redir(cmd, is_parent))
        return (1);
    return 0;
}

void handle_normal_cmd(t_cmd *cmd) {
    pid_t pid;

    pid = fork();
    if (pid == -1)
        exit(1);    // TODO: Handle because there was an error, and exit
    if (pid == 0) {
        // setup redirections
        if (setup_redir(cmd, FALSE))
            exit(EXIT_FAILURE);
        execve(cmd->cmds[0], cmd->cmds, environment);
        // execute cmd
    }
    else {
        // If it's the last cmd, save its pid
    }
}

void exec_cmd(t_cmd *cmd) {
    if (!cmd->cmds)
        exit(1);    // TODO: Handle because there was an error, and exit
    handle_normal_cmd(cmd);
}

void    handle_command(t_ast *root, t_io *io) {
    t_cmd   cmd;

    if (!root || !io)
        return ;
    if (root->type == NODE_COMMAND) {
        setup_cmd(root, io, &cmd);
        exec_cmd(&cmd);
    }
}

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

void clean_tree(t_ast *root)
{
    if (root == NULL)
        return;
    clean_tree(root->left);
    clean_tree(root->right);
    free(root->content); 
    free(root);
}

int main(int argc, char **argv, char **envp)
{
    t_ast *root = NULL;

    environment = envp;
    root = new_node("/usr/bin/ls", NODE_COMMAND);
    root->left = new_node("out.txt", NODE_RED_OTR);
    root->left->left = new_node("Makefile", NODE_RED_IN);
    root->right = new_node("-a", NODE_ARGUMENT);
    root->right->right = new_node("-l", NODE_ARGUMENT);
    execute_job(root);
    clean_tree(root);
    return 0;
}
