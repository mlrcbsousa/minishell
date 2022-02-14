/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:31:58 by msousa            #+#    #+#             */
/*   Updated: 2022/01/07 14:32:16 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstat(t_list *list, unsigned int nbr)
{
	unsigned int	i;

	i = 0;
	while (i++ < nbr)
	{
		if (!list)
			break ;
		list = list->next;
	}
	return (list);
}
