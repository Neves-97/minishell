#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/srcs/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

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

typedef struct s_msh
{
	char	*input;
	char	**env;
	char	**export;
	t_ast	*ast_tmp;
	t_ast	*ast_root;
	t_list	*tokens_tmp;
	t_list	*tokens;
	t_ast	*tmp;
}	t_msh;

typedef struct s_ast
{
	char	*content;
	int		type;
	t_ast	*left;
	t_ast	*right;
}	t_ast;

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
void	free_nodes(void);
void	add_separator(t_msh *data, char sep);
char	*ft_strndup(const char *s, int n);

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

#endif