/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 15:51:20 by msousa            #+#    #+#             */
/*   Updated: 2021/11/08 16:19:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_fabs(double n)
{
	if (n == 0)
		return (0);
	return ((double)ft_ternary(n < 0, -1, 1) * n);
}

/*
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
		printf("%f: %f\n", atof(argv[1]), ft_fabs(atof(argv[1])));
	else
		printf("Error: requires 1 string arg in the form of a float.\n");
	return (0);
}
*/
