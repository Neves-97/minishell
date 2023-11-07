#include "../../includes/minishell.h"

int	setup_redir_cases(t_ast *node, int *in_fd, int *out_fd, t_cmd *cmd)
{
	if (node->type == AST_RDO_TR)
		return (out_tr_redir(node, out_fd));
	else if (node->type == AST_RDO_AP)
		return (out_ap_redir(node, out_fd));
	else if (node->type == AST_RDI)
		return (in_redir(node, in_fd, cmd));
	else if (node->type == AST_RDI_HD)
		return (heredoc_redir(node, in_fd, cmd));
	return (1);
}

int	setup_file_redir(t_cmd *cmd, t_bool is_parent)
{
	t_ast	*tmp;
	int		in_fd;
	int		out_fd;

	tmp = cmd->io->redirection;
	in_fd = -1;
	out_fd = -1;
	while (tmp)
	{
		if (setup_redir_cases(tmp, &in_fd, &out_fd, cmd))
			return (1);
		tmp = tmp->left;
	}
	if (in_fd != -1 && !is_parent)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	return (0);
}
