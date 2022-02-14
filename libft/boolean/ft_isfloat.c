/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:36:36 by msousa            #+#    #+#             */
/*   Updated: 2021/11/08 20:55:48 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isfloat(char *str)
{
	if (!*str)
		return (FALSE);
	if (*str == '-')
		if (!ft_isdigit(*(++str)))
			return (FALSE);
	while (*str && *str != '.')
		if (!ft_isdigit(*str++))
			return (FALSE);
	if (*str == '.')
	{
		if (!ft_isdigit(*(++str)))
			return (FALSE);
		while (*str)
			if (!ft_isdigit(*str++))
				return (FALSE);
	}
	return (TRUE);
}

/*
#include <stdlib.h>
#include <stdio.h>

void	*ft_vternary(int condition, void *a, void *b)
{
	if (condition)
		return (a);
	return (b);
}

char	*should(int condition)
{
	return (ft_vternary(condition, "Succeeded", "Failed"));
}

void	should_not_be_float(char *float_s)
{
	printf("%s -> `%s` should not be a float.\n", 
				 should(!ft_isfloat(float_s)), 
				 float_s);
}

void	should_be_float(char *float_s)
{
	printf("%s -> `%s` should be a float.\n", should(ft_isfloat(float_s)), float_s);
}

int main(int argc, char *argv[])
{
	should_not_be_float("-");
	should_not_be_float("");
	should_not_be_float("-.");
	should_not_be_float(".");
	should_not_be_float("0.1md");
	should_not_be_float("0.0.0");
	should_not_be_float("-0.123.");
	should_be_float("-0");
	should_be_float("-0.0");
	should_be_float("0");
	should_be_float("0.0");
	should_be_float("1.23");
	should_be_float("-1.23");
	should_be_float("-01.0");
	if (argc == 2)
		printf("%f: %d\n", atof(argv[1]), ft_isfloat(argv[1]));
	else
		printf("Error: requires 1 string arg in the form of a float.\n");
	return (0);
}
*/
