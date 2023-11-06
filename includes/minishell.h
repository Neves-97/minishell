#ifndef MINISHELL_H
# define MINISHELL_H

// # include <stdlib.h>
// # include <stdio.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include "../libft/libft.h"
// # include "../libft/ft_printf/srcs/ft_printf.h"
// # include "../libft/get_next_line/get_next_line.h"

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/srcs/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "ft_bool.h"

typedef struct s_ast	t_ast;

# define AST_CMD	0 
# define AST_ARG	1 
# define AST_PIPE	124 
# define AST_AND	38 
# define AST_OR		2 
# define AST_IN		60 
# define AST_OUT	62 
# define AST_RDO_AP	3 
# define AST_RDO_TR 4 
# define AST_RDI_HD	5 
# define AST_RDI	6

# define PATH_MAX 4096

//  exit_status	= integer exit code
// 	default_fd	= default file descriptors for I/O
// 	env			= linked list for the copy of the environment variables
// 	builtins	= builtin linked list
// 	child		= flag to signal if a process is a child process
// 	ast_root	= pointer to the address of the root node of the AST
// 	ast_temp	= temporary AST_CMD node to attatch redirections and AST_ARG
// 	token_list	= head of the token list
// 	temp_token	= temporary t_list struct to build AST

// NODE_RED_IN, // <
//	NODE_RED_HD, // <<
//	NODE_RED_OTR, // >
//	NODE_RED_OAP, // >>
//	NODE_PIPE, // |

// enum e_NodeType
// {
// 	NODE_COMMAND,
// 	NODE_ARGUMENT,
// 	NODE_RED_IN,
// 	NODE_RED_HD,
// 	NODE_RED_OTR,
// 	NODE_RED_OAP,
// 	NODE_PIPE,
// };

enum e_io_cmd_type
{
	SINGLE_CMD,
	FIRST_CMD,
	MIDDLE_CMD,
	LAST_CMD,
};

# ifndef READ
#  define READ 0
# endif
# ifndef WRITE
#  define WRITE 1
# endif

// EOF CTRL D

// typedef struct s_msh
// {
// 	char	*input;
// 	char	**env;
// 	char	**export;
// 	int		exit_status;
// 	int		final_pid;
// 	t_ast	*ast_tmp;
// 	t_ast	*ast_root;
// 	t_list	*tokens_tmp;
// 	t_list	*tokens;
// 	t_ast	*tmp;
// }	t_msh;

typedef struct s_built
{
	char			*cmd;
	int				(*f)(char **str);
	struct s_built	*next;
}	t_built;

typedef struct s_msh
{
	char	c;
	char	*input;
	char	**env;
	int		exit_status;
	int		final_pid;
	int		fd[2];
	t_ast	*ast_tmp;
	t_ast	*ast_root;
	t_list	*tokens_tmp;
	t_list	*tokens;
	t_built	*builtins;
	t_ast	*tmp;
	t_bool	child;
}	t_msh;

typedef struct s_ast
{
	char	*content;
	int		type;
	t_ast	*left;
	t_ast	*right;
}	t_ast;

// typedef struct s_built
// {
// 	char			*cmd;
// 	int				(*f)(char **str);
// 	struct s_built	*next;
// }	t_built;

typedef struct s_io
{
	t_ast	*redirection;
	t_bool	use_pipe[2];
	int		pipe_fd[2];
	int		read_fd;
	int		cmd_type;
}	t_io;

typedef struct s_cmd
{
	int		num_cmds;
	char	**cmds;
	t_io	*io;
}	t_cmd;

// typedef struct s_data
// {
// 	int		exit_status;
// 	int		default_fd[2];
// 	char	*input;
// 	pid_t	last_pid;
// 	t_list	**env;
// 	t_built	*builtins;
// 	t_bool	child;
// 	t_bool	malloc_flag;
// 	t_ast	**ast_root;
// 	t_ast	*ast_temp;
// 	t_list	*token_list;
// 	t_list	*temp_token;
// 	t_cmd	*free_cmd;
// }	t_data;	

//main.c
void	minishell(t_msh *data);
void	setup(t_msh *data, char **envp);
t_msh	*get(void);

// utils.c
int		is_whtspc(char *str);
void	print_list(t_list *head);
void	free_ptp(char **ptp);
char	**dup_ptp(char **ptp);
t_msh	*get(void);

// utils2.c
void	print_ast(t_ast *root, int spaces);
void	free_builtins(void);

// env.c
void	inc_shlvl(char **env);

// lexer.c
void	lexer(t_msh *data);
void	create_token(t_msh *data, int start, int i);
void	delete_empty_tokens(t_list **head);

// lexer_utils.c
void	fill_array(int	*array);
int		is_separator(char c, char *quote);
void	free_nodes(void);
void	add_separator(t_msh *data, char sep);
char	*ft_strndup(const char *s, int n);

// quote_and_expand.c
void	quote_and_expand(t_list *tokens);
int		is_any_quote(char c);

// quote_and_expand_utils.c
int		is_any_quote(char c);

// parser.c
void	parser(void);
void	correct_redir(t_ast *head);

// ast_utils.c
t_ast	*ast_new_node(int type);
void	ast_add_node(t_ast	*parent, t_ast	*child, int right);
void	*free_ast(t_ast	*head);

// and_or.c
t_ast	*and_or(void);
t_ast	*ao_case1(void);
t_ast	*ao_case2(void);
t_ast	*ao_case3(void);

// job.c
t_ast	*job(void);
t_ast	*j_case1(void);
t_ast	*j_case2(void);

// command.c
t_ast	*command(void);

// token_list.c
t_ast	*token_list(void);
t_ast	*tl_case1(void);
t_ast	*tl_case2(void);
t_ast	*tl_case3(void);

// redir.c
t_ast	*redir(void);
t_ast	*redir_case1(void);
t_ast	*redir_case2(void);

// redir_in.c
t_ast	*redir_in(void);
t_ast	*redir_in_case1(void);
t_ast	*redir_in_case2(void);

// redir_out.c
t_ast	*redir_out(void);
t_ast	*redir_out_case1(void);
t_ast	*redir_out_case2(void);

// builtins
int		ft_cd(char	**arg);
int		ft_echo(char **args);
int		ft_env(char **env);
int		ft_export(char **arg);
int		ft_export_arg(char *arg);
void	printf_and_free(char *str);
int		ft_pwd(char **arg);
int		ft_unset(char **arg);
void	ft_unset_arg(char *arg);
// int		ft_exit(void);
int		search_env(char *var);

// access

char	*sub_tild_dir(char *relative);
char	*search_path(char *cmd, char *env_path);
int		is_directory(char *cmd);
int		check_error(char *path);

// and_or 

void	exec_and_or(t_ast *root);
void	execute_helper(char *full_path, t_cmd *cmd);
void	execute(t_cmd *cmd);

// create_ast

int		count_cmds(t_ast *root);
t_built	*init_builtins(void);
void	add_builtin(t_built **list, char *cmd, int (*f)(char **));
int		executor(void);

// error_codes

char	*get_err_msg3(int err_code);
char	*get_err_msg2(int err_code);
char	*get_err_msg(int err_code);
void	display_err_msg(int wstatus);

// BUILTINS/execs.c

t_built	*is_builtin_cmd(char *cmd);
void	exec_cmd(t_cmd *cmd);

// free

void	free_tokens_ast(void);
void	free_them_all(void);

// get_args

void	free_split(char **split);
char	*get_env_value(char *value);
char	**get_argv_env(void);

// handle_cmds.c

void	free_commands(t_cmd *cmd);
void	handle_command(t_ast *root, t_io *io);

// heredoc1
void	here_run(char *eof, int fd);
int		hd_input(char *eof, int fd);
int		handle_hd(t_ast *redir);
int		hd_command(t_ast *root);
int		hd_pipe(t_ast *root);

// heredoc2

int		hd_job(t_ast *root);
int		hd_and_or(t_ast *root);
int		hd_cmd_line(t_ast *root);
int		execute_hd(t_ast *root);

// job

void	execute_job(t_ast *root);

// pipes

void	setup_pipe_bools(t_io *io);
void	execute_pipe(t_ast *root);

// redirs_1.c

int		out_tr_redir(t_ast *node, int *out_fd);
int		out_ap_redir(t_ast *node, int *out_fd);
int		in_redir(t_ast *node, int *in_fd);
int		heredoc_redir(t_ast *node, int *fd);

// redirs_setup.c

int		setup_redir_cases(t_ast *node, int *in_fd, int *out_fd);
int		setup_file_redir(t_cmd *cmd, t_bool is_parent);

// set_up.c

t_io	*setup_io(int io_type, int pipe_fd[2], int read_fd);
char	**create_args(t_ast *root, t_cmd *cmd);
void	setup_cmd(t_ast *root, t_io *io, t_cmd *cmd);
void	setup_pipe_redir(t_cmd *cmd, t_bool is_parent);
int		setup_redir(t_cmd *cmd, t_bool is_parent);

// signals

void	sig_handler(int signum);
void	child_signals(void);
void	ignore_signals(void);
void	parent_signals(void);
void	heredoc_signals(void);

// wait.c

void	wait_exec(void);

// builtins exit

int		ft_exit(char **cmds);
int		validate_code(char **cmds, int i);

void	print_env(char **env);

#endif
