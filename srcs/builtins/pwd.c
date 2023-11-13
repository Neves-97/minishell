/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:13 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 15:41:55 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(char **arg)
{
	char	cwd[PATH_MAX + 1];

	(void) arg;
	if (getcwd(cwd, PATH_MAX + 1))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (0);
	}
	return (0);
}

void	printf_and_free(char *str)
{
	ft_printf("declare -x %s\n", str);
	free (str);
}
