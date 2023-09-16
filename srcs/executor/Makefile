
NAME        := minishell
CC        := cc
FLAGS    := -Wall -Wextra -Werror 

SRCS        :=      set_up.c \
                          create_ast.c \
                          handle_cmds.c \
                          is_builtin.c \
                          redirs_1.c \
                          execs.c \
						  pipes.c \
						  redirs_setup.c \
						  wait.c\
                          
OBJS        := $(SRCS:.c=.o)



.SILENT: 


.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}


RM		    := rm -f

${NAME}:	${OBJS}
			
			${CC} ${FLAGS} -o ${NAME} ${OBJS}

all:		${NAME}

bonus:		all

clean:
			@ ${RM} *.o */*.o */*/*.o

fclean:		clean
			@ ${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re


