NAME		=		minishell

CC			=		cc

CFLAGS		=		-Wall -Wextra -Werror -g -lreadline

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

SRC 		=		srcs/*.c srcs/lexer/*.c ./libft/ft_printf/srcs/*.c

all:		$(NAME)

$(NAME):	$(LIBFT) $(SRC) $(FT_PRINTF)
			$(CC) $(CFLAGS) $(SRC) $(FT_PRINTF) $(GNL) $(LIBFT) $(INCLUDES) -o $(NAME)
		
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
			