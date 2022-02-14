/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:04:55 by msousa            #+#    #+#             */
/*   Updated: 2021/04/12 23:05:03 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*buf;

	if (dest == src || !n)
		return (dest);
	buf = (char *)dest;
	while (n--)
		*(char *)dest++ = *(char *)src++;
	return (buf);
}
