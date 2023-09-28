#include "minishell.h"

int	echo_has_option(char *option)
{
	int	i;

	i = 0;
	if (option[i++] != '-')
		return (0);
	while (option[i])
		if (option[i++] != 'n')
			return (0);
	return (1);
}

int	ft_echo(t_ast	*head)
{
	t_ast	*tmp;
	int		new_line;

	if (!head)
		return (0);
	tmp = head;
	if (!echo_has_option(head->content))
		new_line = 1;
	else
	{
		new_line = 0;
		head = head->right;
	}
	while (head)
	{
		write(1, head->content, ft_strlen(head->content));
		if (head->right)
			write(1, " ", 1);
		head = head->right;
	}
	if (new_line)
		write(1, "\n", 1);
	head = tmp;
	return (1);
}
