#include "../../includes/minishell.h"

// /* Handler for SIGINT in the parent process */


// void	child_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

// /* Ignore SIGINT and SIGQUIT. Handling of these signals can be restored
//    by calling any of the functions in this file */
// void	ignore_signals(void)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, SIG_IGN);
// }

// /* Toggle signals for the parent process */
// void	parent_signals(void)
// {
// 	signal(SIGINT, sig_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

// /* Toggle signals for the heredoc process */
// void	heredoc_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_IGN);
// }
