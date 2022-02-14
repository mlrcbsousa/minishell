/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmin_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:33:44 by msousa            #+#    #+#             */
/*   Updated: 2022/01/07 14:38:11 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstmin_int(t_list *list)
{
	void	*min;

	if (!list)
		return (NULL);
	min = list->content;
	while (list)
	{
		if (*(int *)list->content < *(int *)min)
			min = list->content;
		list = list->next;
	}
	return (min);
}
