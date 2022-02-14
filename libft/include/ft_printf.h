/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 22:36:48 by msousa            #+#    #+#             */
/*   Updated: 2021/11/02 21:50:19 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define PRINTF_FORMATS "cspdiuxX%"
# define PRINTF_DELIMITER '%'

typedef int	(*t_formater)(va_list);

int	ft_printf(const char *format, ...);

int	format_d(va_list ap);
int	format_u(va_list ap);
int	format_x(va_list ap);
int	format_upperx(va_list ap);
int	format_percent(va_list ap);

#endif
