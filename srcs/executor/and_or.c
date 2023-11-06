#include "../../includes/minishell.h"

void	exec_and_or(t_ast *root)
{
	if (!root)
		return ;
	if (root->type == AST_AND)
	{
		exec_and_or(root->left);
		if (get()->exit_status == 0)
			exec_and_or(root->right);
	}
	else if (root->type == AST_OR)
	{
		exec_and_or(root->left);
		if (get()->exit_status != 0)
			exec_and_or(root->right);
	}
	else
		execute_job(root);
}

void	execute_helper(char *full_path, t_cmd *cmd)
{
	if (full_path == NULL)
	{
		free_commands(cmd);
		exit(127);
	}
	execve(full_path, cmd->cmds, get()->env);
	perror(full_path);
	exit(check_error(full_path));
}

/* Execute the command */
void	execute(t_cmd *cmd)
{
	char	*full_path;
	char	*env_path;

	if (cmd->cmds[0][0] == '/' || !ft_strncmp(cmd->cmds[0], "./", 2)
		|| !ft_strncmp(cmd->cmds[0], "../", 3))
	{
		if (!is_directory(cmd->cmds[0]))
			full_path = ft_strdup(cmd->cmds[0]);
	}
	else if (!ft_strncmp(cmd->cmds[0], "~/", 2))
		full_path = sub_tild_dir(cmd->cmds[0]);
	else
	{
		env_path = get_env_value("PATH=");
		if (env_path[0] == '\0')
		{
			ft_putstr_fd(cmd->cmds[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			exit(127);
		}
		full_path = search_path(cmd->cmds[0], env_path);
		execute_helper(full_path, cmd);
	}
}
