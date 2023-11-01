#include "../../includes/minishell.h"

int	count_cmds(t_ast *root)
{
	t_ast	*tmp;
	int		counter;

	if (!root)
		return (0);
	if (root->type != AST_CMD)
		return (0);
	tmp = root;
	counter = 0;
	while (tmp)
	{
		counter++;
		tmp = tmp->right;
	}
	return (counter);
}

// int	execute_hd(t_ast *root)
// {
// 	if (!hd_cmd_line(root))
// 		return (0);
// 	return (1);
// }

int	executor(void)
{
	t_ast	*root;

	root = get()->ast_tmp;
	// execute_hd(root);
	// exec_and_or(root);
	execute_commands(root);
	return (0);
}

void	add_builtin(t_built **list, char *cmd, int (*f)(char **))
{
	t_built	*new;
	t_built	*temp;

	new = (t_built *)malloc(sizeof(t_built));
	if (!new)
		exit(EXIT_FAILURE);
	new->cmd = cmd;
	new->f = f;
	new->next = NULL;
	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_built	*init_builtins(void)
{
	t_built	*head;

	head = NULL;
	add_builtin(&head, "echo", ft_echo);
	add_builtin(&head, "cd", ft_cd);
	add_builtin(&head, "pwd", ft_pwd);
	add_builtin(&head, "export", ft_export);
	add_builtin(&head, "unset", ft_unset);
	add_builtin(&head, "env", ft_env);
	add_builtin(&head, "exit", ft_exit);
	return (head);
}
