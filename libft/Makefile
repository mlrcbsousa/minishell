# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <msousa@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/12 22:41:56 by msousa            #+#    #+#              #
#    Updated: 2022/02/11 15:46:41 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
CC			= gcc
RM			= rm -f
AR			= ar rc

NAME		= libft.a

INC			= -Iinclude
# INC			= -Iincludes \
# 					-Iboolean \
# 					-Iconvert \
# 					-Ilist \
# 					-Imath \
# 					-Imemory \
# 					-Iprint \
# 					-Istring

SRCS		= boolean/ft_isalnum.c \
					boolean/ft_isalpha.c \
					boolean/ft_isascii.c \
					boolean/ft_isdigit.c \
					boolean/ft_isfloat.c \
					boolean/ft_isnumber.c \
					boolean/ft_isnumber_u.c \
					boolean/ft_isprint.c \
					boolean/ft_isspace.c \
					boolean/ft_ternary.c \
					convert/ft_atof.c \
					convert/ft_atoi.c \
					convert/ft_atol.c \
					convert/ft_itoa.c \
					convert/ft_uitoa.c \
					convert/ft_ultoa_base.c \
					list/ft_islstsorted_int.c \
					list/ft_lstadd_back.c \
					list/ft_lstadd_front.c \
					list/ft_lstat.c \
					list/ft_lstclear.c \
					list/ft_lstdelone.c \
					list/ft_lstdup.c \
					list/ft_lstdup_int.c \
					list/ft_lstfind.c \
					list/ft_lstiter.c \
					list/ft_lstlast.c \
					list/ft_lstmap.c \
					list/ft_lstmax_int.c \
					list/ft_lstmin_int.c \
					list/ft_lstnew.c \
					list/ft_lstsize.c \
					list/ft_lstsort.c \
					math/ft_abs.c \
					math/ft_fabs.c \
					math/ft_pow.c \
					math/ft_ullen.c \
					math/ft_ullen_base.c \
					memory/ft_bzero.c \
					memory/ft_calloc.c \
					memory/ft_memccpy.c \
					memory/ft_memchr.c \
					memory/ft_memcmp.c \
					memory/ft_memcpy.c \
					memory/ft_memmove.c \
					memory/ft_memset.c \
					print/ft_printf.c \
					print/ft_printf_formatters.c \
					print/ft_putchar.c \
					print/ft_putchar_fd.c \
					print/ft_putendl.c \
					print/ft_putendl_fd.c \
					print/ft_putnbr_base.c \
					print/ft_putnbr_fd.c \
					print/ft_putstr.c \
					print/ft_putstr_fd.c \
					string/ft_split.c \
					string/ft_strchr.c \
					string/ft_strcmp.c \
					string/ft_strcpy.c \
					string/ft_strdup.c \
					string/ft_streq.c \
					string/ft_strjoin.c \
					string/ft_strlcat.c \
					string/ft_strlcpy.c \
					string/ft_strlen.c \
					string/ft_strmapi.c \
					string/ft_strnchr.c \
					string/ft_strncmp.c \
					string/ft_strnstr.c \
					string/ft_strrchr.c \
					string/ft_strtrim.c \
					string/ft_substr.c \
					string/ft_tolower.c \
					string/ft_toupper.c \
					string/get_next_line.c

OBJS		= ${SRCS:.c=.o}

${NAME}:	${OBJS}
					${AR} $@ $^
					ranlib $@

%.o:%.c
					${CC} ${CFLAGS} ${INC} -c $< -o $@
# libft.h ft_boolean.h ft_printf.h
# ${CC} ${CFLAGS} -c $< -o $@

all:			${NAME}

style:
					-norminette $$( find . -type f \( -name "*.c" -or -name "*.h" \) )

clean:
					${RM} ${OBJS}

fclean: 	clean
					${RM} ${NAME}

re: 			fclean all

.PHONY: re clean fclean all
