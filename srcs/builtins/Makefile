NAME		=		minishell

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -g

INCLUDES	=		-I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(FT_PRINTF_HEADERS)

HEADERS_DIRECTORY = ./includes/

LIBFT		=		./libft/libft.a
LIBFT_INCLUDES =	../libft/libft.h
LIBFT_HEADERS = 	$(LIBFT_INCLUDES)

FT_PRINTF		=		./libft/ft_printf/libftprintf.a
FT_PRINTF_INCLUDES=		./libft/ft_printf/srcs/ft_printf
FT_PRINTF_HEADERS =		$(FT_PRINTF_INCLUDES)

GNL			=		./libft/get_next_line/*.c

RM			=		rm -f

SRC 		=		srcs/*.c srcs/lexer/*.c srcs/parser/*.c srcs/builtins/*.c srcs/errors/*.c ./libft/ft_printf/srcs/*.c

all:		$(NAME)

$(NAME):	$(LIBFT) $(SRC) $(FT_PRINTF)
			$(CC) $(CFLAGS) $(SRC) $(GNL) $(LIBFT) $(INCLUDES) -lreadline -o $(NAME)
		
$(LIBFT):
			make -C ./libft

clean:		
			make clean -C ./libft
			$(RM) $(NAME)
fclean:
			make fclean -C ./libft
			$(RM) $(NAME)

re:		fclean	$(NAME)

bonus:		$(BONUS)
			