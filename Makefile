# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2022/03/01 21:05:52 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror -g
LINKS		= -Llibft -lft -lreadline
CC			= gcc
RM			= rm -f
INC			= -Iinclude -Ilibft/include
UNAME 	:= ${shell uname}
OBJ			= ${SRC:.c=.o}
SRC			= minishell.c \
					src/token.c \
					src/lexer.c \
					src/lexer_1.c \
					src/astree.c \
					src/parser.c \
					src/parser_1.c \
					src/utils/binary_paths.c \
					src/utils/signals.c \
					src/execute.c \
					src/command.c \
					src/builtins.c \
					src/builtins_1.c \
					src/run.c \
					src/utils/binary_paths.c

NAME		= minishell

ifeq (${UNAME}, Linux)
# some Linux only variable set
endif
ifeq (${UNAME}, Darwin)
# some Mac only variable set
endif

${NAME}:	${OBJ}
					${MAKE} -C libft
					${CC} ${CFLAGS} ${OBJ} ${LINKS} -o $@

%.o:%.c
					${CC} ${CFLAGS} ${INC} -c $< -o $@

all:			${NAME}

bonus:		all

style:
					-norminette $$( find . -type f \( -name "*.c" -or -name "*.h" \) )

test:			${NAME}
					-./tests.sh

clean:
					${MAKE} clean -C libft
					${RM} ${OBJ}

fclean:		clean
					${RM} ${NAME}

re: 			fclean all

debug:		INC += -DDEBUG_MODE
debug:		CFLAGS += -g -fsanitize=address
debug:		clean
debug:		all

.PHONY : 	all clean fclean re bonus
