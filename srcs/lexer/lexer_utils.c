/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:09 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:16:10 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_array(int	*array)
{
	array[0] = '|';
	array[1] = '&';
	array[2] = '<';
	array[3] = '>';
	array[4] = ' ';
	array[5] = '\0';
}

int	is_separator(char c, char *quote)
{
	int	type[6];
	int	i;

	if ((quote[0] == 0) && (c == '\"' || c == '\''))
		quote[0] = c;
	else if (quote[0] == c)
		quote[0] = 0;
	fill_array(type);
	i = 0;
	while ((quote[0] == 0) && type[i])
	{
		if (c == type[i++])
			return (1);
	}
	return (0);
}

void	free_nodes(void)
{
	t_list	*tmp;

	while (get()->tokens)
	{
		tmp = get()->tokens->next;
		free (get()->tokens->content);
		free (get()->tokens);
		get()->tokens = tmp;
	}
}

void	add_separator(t_msh *data, char sep)
{
	char	*str;

	str = malloc(sizeof(char) + 1);
	str[0] = sep;
	str[1] = '\0';
	ft_lstadd_back(&(data->tokens), ft_lstnew(str, sep));
}

char	*ft_strndup(const char *s, int n)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_strlen((char *)s) * sizeof(char) + 1));
	if (!str)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
