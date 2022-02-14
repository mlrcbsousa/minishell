/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:10:26 by msousa            #+#    #+#             */
/*   Updated: 2021/04/13 15:32:35 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

	/*size_t	length;

	length = ft_strlen(src);
	while (*dst++ && size && --size + 1)
		length++;
	dst--;
	while (*src && size && --size)
		*dst++ = *src++;
	if (size)
		*dst = '\0';
	return (length);*/

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (i + j + 1 < size && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	while (src[j])
		j++;
	if (i >= size)
		return (j + size);
	else
		return (j + i);
}
