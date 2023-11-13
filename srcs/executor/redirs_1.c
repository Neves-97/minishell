/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:44 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 16:18:16 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	out_tr_redir(t_ast *node, int *out_fd)
{
	if (*out_fd != -1)
		close(*out_fd);
	*out_fd = open(node->content, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (*out_fd == -1)
	{
		free_them_all();
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	out_ap_redir(t_ast *node, int *out_fd)
{
	if (*out_fd != -1)
		close(*out_fd);
	*out_fd = open(node->content, O_CREAT | O_APPEND | O_WRONLY, 0664);
	if (*out_fd == -1)
	{
		free_them_all();
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	in_redir(t_ast *node, int *in_fd, t_cmd *cmd)
{
	if (*in_fd != -1)
		close(*in_fd);
	*in_fd = open(node->content, O_RDONLY, 0664);
	if (*in_fd == -1)
	{
		ft_putstr_fd(node->content, 2);
		ft_putendl_fd(": No such file or directory", 2);
		(void)cmd;
		return (1);
	}
	return (0);
}

int	heredoc_redir(t_ast *node, int *fd, t_cmd *cmd)
{
	(void) node;
	if (*fd != -1)
		close(*fd);
	*fd = open(node->content, O_RDONLY);
	if (*fd == -1)
	{
		free_them_all();
		free_commands(cmd);
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	// if (unlink(node->content) == -1)  pode tar a dar merda
	// {
	// 	free_them_all();
	// 	free_commands(cmd);
	// 	perror("Error unlink");
	// 	exit(EXIT_FAILURE);
	// }
	return (0);
}
