/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:17:25 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 16:17:50 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_streq(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_env_key(char *raw)
{
	int	length;

	length = 0;
	if (ft_isalpha(*raw) || *raw == EXPAND_USCORE)
	{
		raw++;
		length++;
		while (ft_isalnum(*raw) || *raw == EXPAND_USCORE)
		{
			raw++;
			length++;
		}
	}
	return (ft_substr(raw - length, 0, length));
}
