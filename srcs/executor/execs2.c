/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:15 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:14:16 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_built	*is_builtin_cmd(char *cmd)
{
	t_built	*builtin;

	builtin = get()->builtins;
	while (builtin)
	{
		if (!ft_strncmp(cmd, builtin->cmd, ft_strlen(builtin->cmd) + 1))
			return (builtin);
		builtin = builtin->next;
	}
	return (NULL);
}
