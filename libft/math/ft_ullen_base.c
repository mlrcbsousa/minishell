/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullen_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 00:36:59 by msousa            #+#    #+#             */
/*   Updated: 2021/04/24 00:46:36 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ullen_base(unsigned long nbr, int base)
{
	size_t	len;

	len = 1;
	while (nbr / base)
	{
		nbr /= base;
		len++;
	}
	return (len);
}
/*
#include <stdio.h>

int main(void)
{
	// 0
	printf("%d\n", (ft_ullen_base(0, 10) == 1));
	printf("%d\n", (ft_ullen_base(0, 2) == 1));
	printf("%d\n", (ft_ullen_base(0, 8) == 1));
	printf("%d\n", (ft_ullen_base(0, 16) == 1));
	
	// max
	printf("%d\n", (ft_ullen_base(9, 10) == 1));
	printf("%d\n", (ft_ullen_base(1, 2) == 1));
	printf("%d\n", (ft_ullen_base(7, 8) == 1));
	printf("%d\n", (ft_ullen_base(15, 16) == 1));
	
	// limit
	printf("%d\n", (ft_ullen_base(10, 10) == 2));
	printf("%d\n", (ft_ullen_base(2, 2) == 2));
	printf("%d\n", (ft_ullen_base(8, 8) == 2));
	printf("%d\n", (ft_ullen_base(16, 16) == 2));
	
	// high
	printf("%d\n", (ft_ullen_base(234567, 10) == 6));
	printf("%d\n", (ft_ullen_base(11, 2) == 4));
	printf("%d\n", (ft_ullen_base(64, 8) == 3));
	printf("%d\n", (ft_ullen_base(256, 16) == 3));
	
	return (0);
}
*/
