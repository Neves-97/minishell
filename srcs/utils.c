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
	if (tmp)
	{
		while (tmp)
		{
			printf("node %d:%s%%\ntype:  %d\n\n", i, tmp->content, tmp->type);
			tmp = tmp->next;
			i++;
		}
	}
}

void	free_ptp(char **ptp)
{
	int	i;

	i = 0;
	while (ptp && ptp[i])
		free(ptp[i++]);
	free(ptp);
}

char	**dup_ptp(char **ptp)
{
	int		i;
	char	**split;

	i = 0;
	while (ptp && ptp[i])
		i++;
	split = ft_calloc(sizeof(char *), i + 1);
	i = -1;
	while (ptp[++i])
		split[i] = ft_strdup(ptp[i]);
	split[i] = NULL;
	return (split);
}

t_msh	*get(void)
{
	static t_msh	data;

	return (&data);
}

void print_env(char **env) {
	if (!env) {
		printf("Foda-se\n");
		return ;
	}
	for (int i = 0; env[i]; i++)
		printf("%s\n", env[i]);
}
