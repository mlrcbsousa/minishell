/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:04:37 by msousa            #+#    #+#             */
/*   Updated: 2022/01/26 20:19:34 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Uses QuickSort algorithm.

static void	swap(t_list *a, t_list *b)
{
	void	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

static int	partition(t_list *list, int start, int end)
{
	t_list	*pivot;
	t_list	*current;
	int		pivot_index;
	int		i;

	i = start;
	pivot_index = start;
	pivot = ft_lstat(list, end);
	while (i < end)
	{
		current = ft_lstat(list, i);
		if (*(int *)current->content < *(int *)pivot->content)
		{
			swap(current, ft_lstat(list, pivot_index));
			pivot_index++;
		}
		i++;
	}
	swap(ft_lstat(list, pivot_index), pivot);
	return (pivot_index);
}

void	ft_lstsort(t_list *list, int start, int end)
{
	int	index;

	if (start >= end)
		return ;
	index = partition(list, start, end);
	ft_lstsort(list, start, index - 1);
	ft_lstsort(list, index + 1, end);
}

/*
To compile:

```bash
gcc -Wall -Wextra -Werror libft.h ft_lstsort.c ft_lstat.c ft_atoi.c \
ft_lstnew.c ft_lstiter.c ft_lstclear.c ft_isspace.c ft_isdigit.c \
ft_lstdelone.c
```

#include <stdio.h>

void print(void *content)
{
	printf("%d, ", *(int *)content);
}

t_list	*ft_list_push_strs(int size, char **strs)
{
	t_list	*list;
	int	*content;

	if (size == 0)
		return (0);
	
	// Pushing Ints
	content = (int *)malloc(sizeof(*content));
	*content = ft_atoi(*(strs + size - 1));

	list = ft_lstnew(content);
	list->next = ft_list_push_strs(size - 1, strs);
	return (list);
}

int	main(int argc, char *argv[])
{
	t_list	*list;
	
	// turn argv into linked list
	argc--;
	argv++;
	list = ft_list_push_strs(argc, argv);

	// sort
	ft_lstsort(list, 0, argc - 1);

	// print list
	ft_lstiter(list, print);

	// free list
	ft_lstclear(&list, free);

	return (0);
}
*/