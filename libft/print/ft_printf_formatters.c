/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatters_0.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 21:17:13 by msousa            #+#    #+#             */
/*   Updated: 2021/04/22 21:21:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_d(va_list ap)
{
	int		length;
	char	*string;

	string = ft_itoa(va_arg(ap, int));
	length = ft_strlen(string);
	ft_putstr(string);
	if (string)
		free(string);
	return (length);
}

int	format_u(va_list ap)
{
	int		length;
	char	*string;

	string = ft_uitoa(va_arg(ap, unsigned int));
	length = ft_strlen(string);
	ft_putstr(string);
	if (string)
		free(string);
	return (length);
}

int	format_x(va_list ap)
{
	int		length;
	char	*string;

	string = ft_ultoa_base(va_arg(ap, unsigned int), HEX);
	length = ft_strlen(string);
	ft_putstr(string);
	if (string)
		free(string);
	return (length);
}

int	format_upperx(va_list ap)
{
	int		length;
	char	*string;

	string = ft_ultoa_base(va_arg(ap, unsigned int), HEXU);
	length = ft_strlen(string);
	ft_putstr(string);
	if (string)
		free(string);
	return (length);
}

int	format_percent(va_list ap)
{
	(void)ap;
	ft_putchar('%');
	return (1);
}
