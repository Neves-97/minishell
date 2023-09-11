#include "../../includes/minishell.h"

char **environment;




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

    (void) argc;
    (void) argv;

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
