#include "../../includes/minishell.h"

int	out_tr_redir(t_ast *node, int *out_fd)
{
	if (*out_fd != -1)
		close(*out_fd);
	*out_fd = open(node->content, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (*out_fd == -1)
	{
		free_them_all();
		exit(EXIT_FAILURE);		// exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
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
		exit(EXIT_FAILURE);		// exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
	}
	return (0);
}

int	in_redir(t_ast *node, int *in_fd)
{
	if (*in_fd != -1)
		close(*in_fd);
	*in_fd = open(node->content, O_RDONLY, 0664);
	if (*in_fd == -1)
	{
		// free_tokens_ast();
		// free_nodes();
		free_them_all();
		exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
	}
	return (0);
}

int	heredoc_redir(t_ast *node, int *fd)
{
	(void) node;
	if (*fd != -1)
		close(*fd);
	*fd = open(node->content, O_RDONLY);
	if (*fd == -1)
	{
		// TODO: // handle error
		free_tokens_ast();
		free_ptp(get()->env);
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	if (unlink(node->content) == -1)
	{
		// TODO: // handle error
		free_tokens_ast();
		free_ptp(get()->env);
		perror("Error unlink");
		exit(EXIT_FAILURE);
	}
	return (0);
}
