/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:49:38 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:49:39 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup(t_msh *data, char **envp)
{
	data->env = dup_ptp(envp);
	inc_shlvl(data->env);
	data->builtins = init_builtins();
	pqp()[0] = 0;
}

void	inc_shlvl(char **env)
{
	int		i;
	char	*str;
	int		nbr;

	i = 0;
	while ((ft_strncmp(env[i], "SHLVL", 5)))
		i++;
	str = ft_substr(env[i], 6, ft_strlen(env[i]));
	nbr = ft_atoi(str);
	free(str);
	free(env[i]);
	str = (ft_itoa(nbr + 1));
	env[i] = ft_strjoin("SHLVL=", str);
	free(str);
}
