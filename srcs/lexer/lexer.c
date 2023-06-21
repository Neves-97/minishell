#include "minishell.h"

void	lexer(t_msh *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (is_separator(data->input[i + 1]) || \
		i == (int)ft_strlen(data->input) - 1)
			create_token(data, i);
		i++;
	}
}

void	create_token(t_msh *data, int i)
{
	char		*str;
	int			limit;
	int			y;
	int			size;

	limit = i + 1;
	y = 0;
	while (!(is_separator(data->input[i])) && i != 0)
		i--;
	if (is_separator(data->input[i]))
	{
		// ft_lstadd_back(&(data->tokens), data->input[i]);
		i++;
	}
	printf("i: %d\n", i);
	printf("limit: %d\n", limit);
	size = limit - i;
	str = malloc((size) * sizeof(char) + 1);
	while (i != limit)
	{
		str[y++] = data->input[i++];
	}
	str[y] = '\0';
	printf("y: %d\n", y);
	printf("%s$\n\n", str);
	ft_lstadd_back(&(data->tokens), ft_lstnew(str, size));
	free (str);
}


