# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/03 20:25:59 by msousa            #+#    #+#              #
#    Updated: 2022/03/03 20:27:41 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
CC			= gcc
RM			= rm -f
OBJ			= ${SRC:.c=.o}
SRC			= hello.c

NAME		= hello

${NAME}:	${OBJ}
					${CC} ${CFLAGS} ${OBJ} -o $@

%.o:%.c
					${CC} ${CFLAGS} -c $< -o $@

all:			${NAME}

clean:
					${RM} ${OBJ}

fclean:		clean
					${RM} ${NAME}

re: 			fclean all

.PHONY : 	all clean fclean re bonus
