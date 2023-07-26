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

	limit = i + 1;
	while (!(is_separator(data->input[i])) && i != 0)
		i--;
	if (is_separator(data->input[i]))
	{
		if (data->input[i] != 32)
			add_separator(data, data->input[i]);
		i++;
	}
	str = ft_strndup(&data->input[i], limit - i);
	if (!(is_whtspc(str)))
		ft_lstadd_back(&(data->tokens), ft_lstnew(str));
	else
		free (str);
}
