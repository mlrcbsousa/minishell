/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 19:32:01 by msousa            #+#    #+#             */
/*   Updated: 2021/04/23 20:20:00 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(long long nb, char *radix)
{
	size_t	base;

	if (!radix)
		return ;
	base = ft_strlen(radix);
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb > (long long)base - 1)
		ft_putnbr_base(nb / base, radix);
	ft_putchar(radix[nb % base]);
}

/*
int main(void)
{
	// hex
	ft_putstr("-1234 in hexadecimal: (-4d2)\n");
	ft_putnbr_base(-1234, HEX);
	ft_putstr("\n\n");
	
	// hexu
	ft_putstr("-1234 in hexadecimal uppercase: (-4D2)\n");
	ft_putnbr_base(-1234, HEXU);
	ft_putstr("\n\n");

	// binary 
	ft_putstr("-200 in binary: (-11001000)\n");
	ft_putnbr_base(-200, BINARY);
	ft_putstr("\n\n");
	
	// octal
	ft_putstr("100 in octal: (144)\n");
	ft_putnbr_base(100, OCTAL);
	ft_putstr("\n\n");

	return (0);
}
*/
