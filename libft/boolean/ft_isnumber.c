/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:48:55 by msousa            #+#    #+#             */
/*   Updated: 2022/02/10 18:55:57 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isnumber(char *str)
{
	if (*str == '-')
		str++;
	return (ft_isnumber_u(str));
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	if (argc == 2)
    printf("%s : %d\n", argv[1], ft_isnumber(argv[1]));
	else
		printf("Error: requires 1 argument.\n");
	return (0);
}
*/
