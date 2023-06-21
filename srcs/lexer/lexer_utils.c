#include "minishell.h"

void	fill_array(int	*array)
{
	array[0] = ' ';
	array[1] = '$';
	array[2] = '?';
	array[3] = '|';
	array[4] = '&';
	array[5] = ';';
	array[6] = '\'';
	array[7] = '\"';
	array[8] = '<';
	array[9] = '>';
	array[10] = '\\';
	array[11] = '(';
	array[12] = ')';
	array[13] = '{';
	array[14] = '}';
	array[15] = '\0';
}

int	is_separator(char c)
{
	int	type[15];
	int	i;

	fill_array(type);
	i = 0;
	while (type[i])
	{
		if (c == type[i++])
			return (type[i]);
	}
	return (0);
}

void	free_nodes(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		free (head->content);
		free (head);
		head = tmp;
	}
}
