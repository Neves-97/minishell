NAME		=		minishell

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -g

INCLUDES	=		-I$(HEADERS_DIRECTORY) -I$(LIBFT_HEADERS) -I$(FT_PRINTF_HEADERS)

HEADERS_DIRECTORY = ./includes/

LIBFT		=		./libft/libft.a
LIBFT_INCLUDES =	../libft/libft.h
LIBFT_HEADERS = 	$(LIBFT_INCLUDES)

FT_PRINTF		=		./libft/ft_printf/libftprintf.a
FT_PRINTF_INCLUDES=		./libft/ft_printf/srcs/ft_printf.h
FT_PRINTF_HEADERS =		$(FT_PRINTF_INCLUDES)

GNL			=		./libft/get_next_line/*.c

RM			=		rm -f

SRC 		=		srcs/*.c ./libft/ft_printf/srcs/*.c

SRCB		=		./checker_src/*.c ./libft/get_next_line/*.c srcs/check.c srcs/error.c srcs/get_values.c srcs/instructions2.c srcs/instructions3.c srcs/instructions.c srcs/make_moves.c srcs/sort.c srcs/sort_utils.c srcs/utils.c

all:		$(NAME)

$(NAME):	$(LIBFT) $(SRC) $(FT_PRINTF)
			$(CC) $(CFLAGS) $(SRC) $(FT_PRINTF) $(LIBFT) $(INCLUDES) -o $(NAME)
		
$(LIBFT):
			make -C ./libft

clean:		
			make clean -C ./libft
			$(RM) $(NAME)
fclean:
			make fclean -C ./libft
			$(RM) $(NAME)
			$(RM) $(BONUS)

re:		fclean	$(NAME)

bonus:		$(BONUS)
			