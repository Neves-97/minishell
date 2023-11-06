#include "../../includes/minishell.h"

void	wait_exec(void)
{
	pid_t	pid;
	int		wstatus;

	while (1)
	{
		pid = waitpid(-1, &wstatus, 0);
		signal(2, sig_handler);
		if (pid <= 0)
			return ;
		if (pid == get()->final_pid)
		{
			if (WIFEXITED(wstatus))
				get()->exit_status = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
			{
				get()->exit_status = WTERMSIG(wstatus) + 128;
				//TODO: FIX ERROR MSG.
				// free_tokens_ast();
				// free_ptp(get()->env);
				free_them_all();
				exit(EXIT_FAILURE);
			}
		}
	}
}
