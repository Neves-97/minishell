/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:09 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 22:17:35 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*put_quotes_on_env(char *arg)
{
	int		i;
	char	*content;
	char	*var;
	char	*tmp;

	i = 0;
	while (arg[i] != '=')
		i++;
	tmp = ft_substr(arg, i + 1, ft_strlen(arg));
	var = ft_substr(arg, 0, i + 1);
	content = ft_strjoin(var, "\"");
	free (var);
	var = ft_strjoin(content, tmp);
	free (content);
	free (tmp);
	content = ft_strjoin(var, "\"");
	free (var);
	return (content);
}

int	export_no_args(void)
{
	int		i;
	char	c;

	i = 0;
	c = 'A';
	while (c != 'z')
	{
		if (!get()->env[i])
		{
			c++;
			i = 0;
		}
		if (get()->env[i][0] == c)
			printf_and_free(put_quotes_on_env(get()->env[i]));
		if (c == 'Z')
			c = 'a';
		if (c == 'z')
			break ;
		i++;
	}
	return (0);
}

int	export_check(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export_arg(char *arg)
{
	int		i;
	char	**new_env;

	if (!export_check(arg))
		return (1);
	i = ft_strlen(arg);
	is_set(arg);
	i = 0;
	while (get()->env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (get()->env[i])
	{
		new_env[i] = ft_strdup(get()->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	free_ptp(get()->env);
	get()->env = new_env;
	return (0);
}

int	ft_export(char **arg)
{
	int	i;

	i = 1;
	if (!arg[i])
		return (export_no_args());
	while (arg[i])
		ft_export_arg(arg[i++]);
	return (0);
}
