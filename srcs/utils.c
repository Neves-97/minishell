#include "minishell.h"

int	is_whtspc(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!((str[i] >= 9 && str[i] <= 13) || \
		str[i] == 32 || str[i] == '\0' || \
		str[i] == '\n'))
			return (0);
		i++;
	}
	return (1);
}

void	print_list(t_list *head)
{
	t_list	*tmp;
	int		i;

	i = 1;
	tmp = head;
	while (tmp)
	{
		printf("node %d:%s$\n", i, tmp->content);
		tmp = tmp->next;
		i++;
	}
}
