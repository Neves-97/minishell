/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:57:09 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 22:16:55 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_set(char *arg)
{
	int		max;
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = ft_strlen(arg);
	while (arg[j] != '=')
		j--;
	tmp = ft_substr(arg, 0, j);
	while (get()->env[i])
		i++;
	max = i;
	i = search_env(tmp);
	if (i < max)
	{
		ft_unset_arg(tmp);
		free(tmp);
		return (1);
	}
	free (tmp);
	return (0);
}
