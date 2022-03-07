/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 23:11:12 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 11:25:14 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Let segfault when str is NULL so we know not to call funciton on NULL
size_t	ft_strlen(const char *str)
{
	size_t	length;

	length = 0;
	while (*str++)
		length++;
	return (length);
}
