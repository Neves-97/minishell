/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_and_expand_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:14 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:16:15 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_qt(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	check_hd(t_list *tokens, t_list *head)
{
	t_list	*tmp;
	int		i;

	i = 0;
	while (tokens->content[i] && tokens->content[i] != '$')
		i++;
	if (i == (int)ft_strlen(tokens->content))
		return (0);
	tmp = head;
	while (head && head->next)
	{
		if (head->content[0] == '<' && head->next->content[0] == '<')
		{
			if (head->next->next == tokens)
				return (1);
		}
		head = head->next;
	}
	head = tmp;
	return (0);
}
