/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:12:59 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 16:21:30 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		if (!arg[i])
			return (0);
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int		has_flag;
	int		i;

	if (args[1])
		has_flag = check_n(args[1]);
	else
		has_flag = 0;
	i = 1;
	if (!args || !args[0])
		return (1);
	i = 1 + has_flag;
	while (args[i]) 
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!has_flag)
		ft_putstr_fd("\n", 1);
	get()->exit_status = 0;
	return (get()->exit_status);
}
