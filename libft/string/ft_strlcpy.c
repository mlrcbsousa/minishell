/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:10:52 by msousa            #+#    #+#             */
/*   Updated: 2021/04/13 16:49:23 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*buf;

	if (!dst || !src)
		return (0);
	buf = src;
	if (src && dst && size)
	{
		while (*src && --size)
			*dst++ = *src++;
		*dst = 0;
	}
	return (ft_strlen(buf));
}
