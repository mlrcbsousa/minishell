/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 00:25:11 by msousa            #+#    #+#             */
/*   Updated: 2021/04/24 01:42:00 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_uistr(char *str, unsigned int n)
{
	if (n > 9)
		ft_uistr(str - 1, n / 10);
	*str = n % 10 + 48;
}

char	*ft_uitoa(unsigned int n)
{
	char		*str;
	size_t		len;

	len = ft_ullen(n);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	ft_uistr(str + len - 1, n);
	*(str + len) = '\0';
	return (str);
}
