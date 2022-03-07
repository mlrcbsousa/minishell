/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 22:45:50 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 12:21:44 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	format_c(va_list ap)
{
	ft_putchar(va_arg(ap, int));
	return (1);
}

static int	format_s(va_list ap)
{
	char	*string;
	int		length;

	string = va_arg(ap, char *);
	if (!string)
		string = "(null)";
	length = ft_strlen(string);
	ft_putstr(string);
	return (length);
}

static int	format_p(va_list ap)
{
	char	*string;
	int		length;

	string = ft_ultoa_base(va_arg(ap, unsigned long), HEX);
	length = ft_strlen(string);
	if (string && *string)
		ft_putstr("0x");
	ft_putstr(string);
	if (string)
		free(string);
	return (2 + length);
}

static void	assign_formatters(t_formater *formatters)
{
	*formatters++ = format_c;
	*formatters++ = format_s;
	*formatters++ = format_p;
	*formatters++ = format_d;
	*formatters++ = format_d;
	*formatters++ = format_u;
	*formatters++ = format_x;
	*formatters++ = format_upperx;
	*formatters++ = format_percent;
}

int	ft_printf(const char *string, ...)
{
	int			length;
	va_list		ap;
	t_formater	formatters[9];

	assign_formatters(formatters);
	length = 0;
	va_start(ap, string);
	while (*string)
	{
		if (*string == PRINTF_DELIMITER
			&& ft_strnchr(PRINTF_FORMATS, *(string + 1)) != -1)
			length += formatters[ft_strnchr(PRINTF_FORMATS, *(++string))](ap);
		else
		{
			ft_putchar(*string);
			length++;
		}
		string++;
	}
	va_end(ap);
	return (length);
}
