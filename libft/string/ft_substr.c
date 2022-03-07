/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:13:39 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 14:53:20 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	const char		*save;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	while (start--)
		s++;
	i = 0;
	save = s;
	while (*s && i < len)
	{
		s++;
		i++;
	}
	str = (char *)malloc(sizeof(*s) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, save, i + 1);
	return (str);
}
