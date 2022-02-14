/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:20:13 by msousa            #+#    #+#             */
/*   Updated: 2021/11/08 14:25:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	nb;
	int	power;

	if (argc == 3)
	{
		nb = atoi(argv[1]);
		power = atoi(argv[2]);
		printf("%d ^ %d : %ld\n", nb, power, ft_pow(nb, power));
	}
	else
		printf("Error: requires 2 args, 1st (int)nb, 2nd (int)power.\n");
	return (0);
}
*/
