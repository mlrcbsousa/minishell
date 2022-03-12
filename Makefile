# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <msousa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2022/03/12 16:56:37 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror `pkg-config readline --cflags` -g
LINKS		= -Llibft -lft `pkg-config readline --libs`
CC			= gcc
RM			= rm -f
INC			= -Iinclude -Ilibft/include
OBJ			= ${SRC:.c=.o}
SRC			= minishell.c \
					src/token.c \
					src/lexer.c \
					src/lexer_1.c \
					src/lexer_2.c \
					src/astree.c \
					src/parser.c \
					src/parser_1.c \
					src/parser_2.c \
					src/parser_3.c \
					src/utils/binary_paths.c \
					src/utils/signals.c \
					src/utils/helpers.c \
					src/utils/helpers_1.c \
					src/utils/helpers_2.c \
					src/execute.c \
					src/execute_1.c \
					src/command.c \
					src/builtins.c \
					src/builtins_1.c \
					src/builtins_2.c \
					src/run.c \
					src/run_1.c \
					src/run_2.c \
					src/env.c \
					src/env_1.c \
					src/test.c \
					src/script.c \
					src/redirect.c

NAME		= minishell

${NAME}:	${OBJ}
					${MAKE} -C libft
					${CC} ${CFLAGS} ${OBJ} ${LINKS} -o $@

%.o:%.c
					${CC} ${CFLAGS} ${INC} -c $< -o $@

all:			${NAME}

bonus:		all

style:
					-norminette src minishell.c include tests libft

test:			${NAME}
					-./tests/tests.sh

check:
					-cat minishell.c src/*/* | grep TODO

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
