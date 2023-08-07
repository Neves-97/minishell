#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/srcs/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

typedef struct s_msh
{
	char	*input;
	t_list	*tokens;
}	t_msh;

enum e_token_type
{
	DEF_CHAR	= -1,
	SPACE_CHAR	= ' ',
	USD_CHAR	= '$',
	QM_CHAR		= '?',
	PIPE_CHAR	= '|',
	AND_CHAR	= '&',
	SC_CHAR		= ';',
	QUOTE_CHAR	= '\'',
	DQUOTE_CHAR	= '\"',
	INRED_CHAR	= '<',
	OUTRED_CHAR	= '>',
	ESC_CHAR	= '\\',
	OP_CHAR		= '(',
	CP_CHAR		= ')',
	OCB_CHAR	= '{',
	CCB_CHAR	= '}',
	NULL_CHAR	= '\0'
};

//main.c
int		main(int ac, char **av, char **envp);
void	minishell(t_msh *data);

// utils.c
int		is_whtspc(char *str);
void	print_list(t_list *head);

// lexer.c
void	lexer(t_msh *data);
void	create_token(t_msh *data, int i);

// lexer_utils.c
void	fill_array(int	*array);
int		is_separator(char c);
void	free_nodes(t_list *head);
void	add_separator(t_msh *data, char sep);
char	*ft_strndup(const char *s, int n);

#endif