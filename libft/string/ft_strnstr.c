/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:12:37 by msousa            #+#    #+#             */
/*   Updated: 2021/04/12 23:12:46 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*buf;

	if (!*s2)
		return ((char *)s1);
	while (*s1 && n)
	{
		buf = (char *)s2;
		if (*s1 == *s2)
		{
			while (*s2
				&& *(s1 + (s2 - buf)) == *s2
				&& (size_t)(s2 - buf) < n)
				s2++;
			if (!*s2)
				return ((char *)s1);
			s2 = buf;
		}
		n--;
		s1++;
	}
	return (NULL);
}
