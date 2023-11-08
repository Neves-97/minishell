/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:04 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:13:05 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_code(char **cmds, int i)
{
	if (cmds[1] && cmds[2])
	{
		if (!get()->child)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	while (cmds[1] && cmds[1][i])
	{
		if (!ft_isdigit(cmds[1][i++]))
		{
			if (!get()->child)
				ft_putstr_fd("exit\n", STDOUT_FILENO);
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmds[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			free_ptp(get()->env);
			free_builtins();
			free_tokens_ast();
			free(cmds);
			get()->exit_status = 2;
			exit(get()->exit_status);
		}
	}
	return (0);
}

int	ft_exit(char **cmds)
{
	static int	i;

	if (cmds[1] && (cmds[1][0] == '-' || cmds[1][0] == '+'))
		i++;
	if (validate_code(cmds, i) == 1)
		return (1);
	if (cmds[1])
	{
		if (!get()->child)
			ft_putstr_fd("exit\n", STDOUT_FILENO);
		get()->exit_status = ft_atoi(cmds[1]);
		free_ptp(get()->env);
		free_tokens_ast();
		free(cmds);
		free_builtins();
		exit(get()->exit_status);
	}
	if (!get()->child)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	free_ptp(get()->env);
	free_tokens_ast();
	free_builtins();
	free(cmds);
	exit(get()->exit_status);
	return (0);
}
