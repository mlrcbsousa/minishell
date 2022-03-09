/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:05:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 17:34:58 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_string_arrays(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

char	**ft_split_first(char const *s, char c)
{
	char	**strs;
	int		i;

	if (!s || !c)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (s[i] != c)
		return (NULL);
	strs = malloc(sizeof(char *) * 3);
	if (!strs)
		return (NULL);
	strs[0] = malloc(sizeof(char) * (i + 1));
	if (!strs[0])
		return (strs);
	ft_strlcpy(strs[0], s, i + 1);
	strs[1] = malloc(sizeof(char) * (ft_strlen(ft_strchr(s, c))));
	if (!strs[1])
		return (strs);
	ft_strlcpy(strs[1], &ft_strchr(s, c)[1], ft_strlen(ft_strchr(s, c)));
	strs[2] = NULL;
	return (strs);
}

t_bool	is_valid_identifier(char *str)
{
	int	i;

	if (!str)
		return (FALSE);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (FALSE);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
