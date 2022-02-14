/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 13:13:00 by msousa            #+#    #+#             */
/*   Updated: 2021/10/09 13:17:29 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strnchr(const char *str, int c)
{
	int	index;

	index = 0;
	while (*str)
	{
		if (*str++ == (char)c)
			return (index);
		index++;
	}
	return (-1);
}
