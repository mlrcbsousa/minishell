/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdup_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:14:52 by msousa            #+#    #+#             */
/*   Updated: 2022/02/08 21:16:21 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstdup_int(t_list *list)
{
	t_list	*new;
	t_list	*tmp;
	int		*content;

	new = 0;
	while (list)
	{
		content = (int *)malloc(sizeof(*content));
		if (!content)
			return (0);
		*content = *(int *)list->content;
		tmp = ft_lstnew(content);
		if (!tmp)
			return (0);
		ft_lstadd_back(&new, tmp);
		list = list->next;
	}
	return (new);
}
