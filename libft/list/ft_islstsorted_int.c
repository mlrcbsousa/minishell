/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islstsorted_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:48:16 by msousa            #+#    #+#             */
/*   Updated: 2022/01/07 14:49:39 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_islstsorted_int(t_list *list)
{
	if (!list)
		return (FALSE);
	while (list->next)
	{
		if (*(int *)list->content > *(int *)list->next->content)
			return (FALSE);
		list = list->next;
	}
	return (TRUE);
}
