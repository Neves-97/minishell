/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:53:14 by ratavare          #+#    #+#             */
/*   Updated: 2023/06/21 12:37:50 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int size)
{
	t_list	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = malloc(sizeof(char) * size + 1);
	while (i < size)
	{
		new->content[i] = content[i];
		i++;
	}
	new->content[i] = '\0';
	new->next = NULL;
	return (new);
}
