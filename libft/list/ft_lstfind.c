/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:23:06 by msousa            #+#    #+#             */
/*   Updated: 2022/01/07 14:24:03 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstfind(t_list *list, void *data, int (*cmp)())
{
	while (list)
	{
		if (cmp(list->content, data))
			break ;
		list = list->next;
	}
	return (list);
}
