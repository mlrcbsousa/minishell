/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:05:21 by msousa            #+#    #+#             */
/*   Updated: 2021/04/13 16:12:26 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 	if (!dst && !src)
		return (NULL);
	while (n--)
		*(char *)(dst + n) = *(char *)(src + n);
	return (dst);
*/

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	int				i;
	unsigned char	*dst_uc;
	unsigned char	*src_uc;

	dst_uc = (unsigned char *)dst;
	src_uc = (unsigned char *)src;
	i = n - 1;
	if (src_uc < dst_uc)
	{
		while (i >= 0)
		{
			dst_uc[i] = src_uc[i];
			i--;
		}
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
