/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:14:52 by msousa            #+#    #+#             */
/*   Updated: 2022/01/26 20:36:31 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup(t_list *list)
{
	t_list	*new;
	t_list	*tmp;

	new = 0;
	while (list)
	{
		tmp = ft_lstnew(list->content);
		if (!tmp)
			return (0);
		ft_lstadd_back(&new, tmp);
		list = list->next;
	}
	return (new);
}
