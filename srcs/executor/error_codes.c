/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_codes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:44 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:13:44 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_err_msg3(int err_code)
{
	if (err_code == 24)
		return (ft_strdup("CPU time limit exceeded"));
	else if (err_code == 25)
		return (ft_strdup("File size limit exceeded"));
	else if (err_code == 26)
		return (ft_strdup("Virtual timer expired"));
	else
		return (ft_strdup(""));
}

char	*get_err_msg2(int err_code)
{
	if (err_code == 12)
		return (ft_strdup("User defined signal 2"));
	else if (err_code == 13)
		return (ft_strdup("Broken pipe"));
	else if (err_code == 14)
		return (ft_strdup("Alarm clock"));
	else if (err_code == 15)
		return (ft_strdup("Terminated"));
	else if (err_code == 16)
		return (ft_strdup("Stack fault"));
	else if (err_code == 17)
		return (ft_strdup("Child process has stopped or terminated"));
	else if (err_code == 18)
		return (ft_strdup("Continued"));
	else if (err_code == 19)
		return (ft_strdup("Stopped"));
	else if (err_code == 20 || err_code == 21)
		return (ft_strdup("Stopped (tty input)"));
	else if (err_code == 22)
		return (ft_strdup("Stopped (tty output)"));
	else if (err_code == 23)
		return (ft_strdup("Urgent I/O condition"));
	else
		return (get_err_msg3(err_code));
}

char	*get_err_msg(int err_code)
{
	if (err_code == 1)
		return (ft_strdup("Hangup"));
	else if (err_code == 2)
		return (ft_strdup(""));
	else if (err_code == 3)
		return (ft_strdup("Quit"));
	else if (err_code == 4)
		return (ft_strdup("Illegal Instruction"));
	else if (err_code == 5)
		return (ft_strdup("Trace/breakpoint trap"));
	else if (err_code == 6)
		return (ft_strdup("Aborted"));
	else if (err_code == 7)
		return (ft_strdup("Bus error"));
	else if (err_code == 8)
		return (ft_strdup("Floating point exception"));
	else if (err_code == 9)
		return (ft_strdup("Killed"));
	else if (err_code == 10)
		return (ft_strdup("User defined signal 1"));
	else if (err_code == 11)
		return (ft_strdup("Segmentation fault"));
	else
		return (get_err_msg2(err_code));
}

void	display_err_msg(int wstatus)
{
	char	*err_msg;
	int		err_code;

	err_code = WTERMSIG(wstatus);
	err_msg = get_err_msg(err_code);
	if (err_msg)
	{
		ft_putstr_fd(err_msg, STDERR_FILENO);
		free(err_msg);
	}
	if (WCOREDUMP(wstatus))
		ft_putstr_fd(" (core dumped)", STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
