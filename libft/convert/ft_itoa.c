/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:51:13 by msousa            #+#    #+#             */
/*   Updated: 2021/04/24 01:41:21 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_llstr(char *str, long long n)
{
	if (n > 9)
		ft_llstr(str - 1, n / 10);
	*str = n % 10 + 48;
}

char	*ft_itoa(int n)
{
	char		*str;
	long long	n_ll;
	size_t		len;

	n_ll = (long long)n;
	if (n < 0)
		n_ll = -n_ll;
	len = ft_ullen(n_ll);
	if (n < 0)
		len++;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
		*str = '-';
	ft_llstr(str + len - 1, n_ll);
	*(str + len) = '\0';
	return (str);
}
