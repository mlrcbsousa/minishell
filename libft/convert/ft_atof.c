/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:48:13 by msousa            #+#    #+#             */
/*   Updated: 2021/11/11 17:51:56 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_atof_process(t_bool *afterdot, double *scale, char *str,
														double *n)
{
	if (*afterdot)
	{
		*scale = *scale / 10;
		*n = *n + (*str - '0') * *scale;
	}
	else if (*str == '.')
		*afterdot = TRUE;
	else
		*n = *n * 10.0 + (*str - '0');
}

double	ft_atof(char *str)
{
	double	n;
	int		afterdot;
	double	scale;
	int		sign;

	afterdot = FALSE;
	scale = 1.0;
	sign = 1;
	n = 0.0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		ft_atof_process(&afterdot, &scale, str, &n);
		str++;
	}
	return (sign * n);
}

/*
#include <stdio.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
		printf("%s: %f\n", argv[1], ft_atof(argv[1]));
	else
		printf("Error: requires 1 string arg in the form of a float.\n");
	return (0);
}
*/
