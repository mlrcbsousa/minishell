/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmax_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:13 by msousa            #+#    #+#             */
/*   Updated: 2022/01/07 14:41:38 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstmax_int(t_list *list)
{
	void	*max;

	if (!list)
		return (NULL);
	max = list->content;
	while (list)
	{
		if (*(int *)list->content > *(int *)max)
			max = list->content;
		list = list->next;
	}
	return (max);
}
