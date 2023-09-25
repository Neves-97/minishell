#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "../libft/libft.h"
# include "../libft/ft_printf/srcs/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "ft_bool.h"

// exit_status = integer exit code
// 	default_fd	= default file descriptors for I/O
// 	env			= linked list for the copy of the environment variables
// 	builtins	= builtin linked list
// 	child		= flag to signal if a process is a child process
// 	ast_root	= pointer to the address of the root node of the AST
// 	ast_temp	= temporary AST_CMD node to attatch redirections and AST_ARG
// 	token_list	= head of the token list
// 	temp_token	= temporary t_token struct to build AST



enum NodeType 
{
    NODE_COMMAND,
    NODE_ARGUMENT,
    NODE_RED_IN,    // <
    NODE_RED_HD,    // <<
    NODE_RED_OTR,   // >
    NODE_RED_OAP,   // >>
	NODE_PIPE,		// |
};

enum io_cmd_type
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

// AST

typedef struct s_ast
{
    char    *content;
    int     type;
    struct s_ast   *left;
    struct s_ast   *right;
} t_ast;

typedef struct s_token
{
	char *str;
}	t_token;

typedef struct s_built
{
	char			*cmd;
	int				(*f)(char **str);
	struct s_built	*next;
}	t_built;

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

typedef struct s_data
{
	int		exit_status;
	int		default_fd[2];
	char	*input;
	pid_t	last_pid;
	t_list	**env;
	t_built	*builtins;
	t_bool	child;
	t_bool	malloc_flag;
	t_ast	**ast_root;
	t_ast	*ast_temp;
	t_token	*token_list;
	t_token	*temp_token;
	t_cmd	*free_cmd;
}	t_data;	

// EXEC

# define AST_CMD	0
# define AST_ARG	1
# define AST_PIPE	124


typedef struct s_msh
{
	char	*input;
	char	**env;
	char	**export;
	int		exit_status;
	int 	final_pid;
	t_ast	*ast_tmp;
	t_ast	*ast_root;
	t_list	*tokens_tmp;
	t_list	*tokens;
}	t_msh;

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

// env.c
void	inc_shlvl(char **env);

// lexer.c
void	lexer(t_msh *data);
void	create_token(t_msh *data, int i);

// lexer_utils.c
void	fill_array(int	*array);
int		is_separator(char c);
void	free_nodes(t_list *head);
void	add_separator(t_msh *data, char sep);
char	*ft_strndup(const char *s, int n);

// parser.c
void	parser(void);

// job.c
t_ast	*job(void);
t_ast	*j_case1(void);

// ast_utils.c
t_ast	*ast_new_node(int type);
void	ast_add_node(t_ast	*parent, t_ast	*child, int right);

// command.c
t_ast	*command(void);

// token_list.c
t_ast	*token_list(void);
t_ast	*tl_case1(void);
t_ast	*tl_case2(void);

// builtins // echo.c
int	check_flag(char **cmd);
int ft_echo(char **cmd);

// is_builtin
bool is_builtin(t_token *token);
int ft_strcmp(const char *s1, const char *s2);

// execver
void execute_command(char **args, char **envp);

// errors / errors.c
void execve_error(void);

// BUILTINS/create_ast
t_ast *new_node(const char *data, int type);
t_ast *insert(t_ast *root, const char *data, int type);
int count_cmds(t_ast *root);
void print_array(char **arr);
void clean_tree(t_ast *root);
int main(int argc, char **argv, char **envp);

// BUILTINS/execs.c

void    execute_job(t_ast *root);
void exec_ast(t_ast *root);
void exec_cmd(t_cmd *cmd);

// BUILTINS/handle_cmds.c

void handle_normal_cmd(t_cmd *cmd);
void    handle_command(t_ast *root, t_io *io);

// BUILTINS/redirs_1.c

int out_tr_redir(t_ast *node, int *out_fd);
int out_ap_redir(t_ast *node, int *out_fd);
int in_redir(t_ast *node, int *in_fd);
int heredoc_redir(t_ast *node, int *fd);

// BUILTINS/redirs_setup.c

int setup_redir_cases(t_ast *node, int *in_fd, int *out_fd);
int setup_file_redir(t_cmd *cmd, t_bool is_parent);

// BUILTINS/set_up.c

void    setup_pipe_bools(t_io *io);
t_io    *setup_io(int io_type, int pipe_fd[2], int read_fd);
char **create_args(t_ast *root, t_cmd *cmd);
void    setup_cmd(t_ast *root, t_io *io, t_cmd *cmd);
int setup_redir(t_cmd *cmd, t_bool is_parent);

// BUILTINS/pipes.c

void    setup_pipe_bools(t_io *io);
void    execute_pipe(t_ast *root);

// SIGNALS/signal_handle.c

void	sig_handler(int signum);
void	child_signals(void);
void	ignore_signals(void);
void	parent_signals(void);

// BUILTINS/wait.c

void	wait_exec(void);

#endif