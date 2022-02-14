/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:15:21 by manuel            #+#    #+#             */
/*   Updated: 2022/02/11 15:25:56 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>

# include "ft_boolean.h"
# include "ft_printf.h"

# include "libft_boolean.h"
# include "libft_convert.h"
# include "libft_list.h"
# include "libft_math.h"
# include "libft_memory.h"
# include "libft_print.h"
# include "libft_string.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef STDIN
#  define STDIN 0
# endif

# ifndef STDOUT
#  define STDOUT 1
# endif

# ifndef STDERR
#  define STDERR 2
# endif

# define DECIMAL "0123456789"
# define HEX "0123456789abcdef"
# define HEXU "0123456789ABCDEF"
# define BINARY "01"
# define OCTAL "01234567"

#endif
