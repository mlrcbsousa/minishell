/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:43:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 16:17:38 by msousa           ###   ########.fr       */
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
	int length;

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

char	*get_expanded(char *raw, t_env *env)
{
	char *expanded;
	char *save;
	char *part;
	char *env_key;

	// TODO: trim quotes

	save = ft_strdup("");

	// only if double quotes or no quotes
	// TODO: not if just open double quote
	if (*raw == LEXICAL_QUOTE)
		return (ft_strdup(raw));

	while (*raw)
	{
		// enter when valid to find a var key
		if (*raw == EXPAND_DOLLAR && *(raw + 1) == EXPAND_QUESTION)
		{
			part = ft_itoa(g_return);
			raw++;
		}
		else if (*raw == EXPAND_DOLLAR
			&& (ft_isalnum(*(raw + 1)) || *(raw + 1) == EXPAND_USCORE))
		{
			env_key = find_env_key(raw + 1);
			part = get_env(env_key, env);
			part = ft_strcpy((char *)malloc(ft_strlen(part) + 1), part);
			raw = raw + ft_strlen(env_key);
			free(env_key);
		}
		else
			part = ft_substr(raw, 0, 1);
		expanded = ft_strjoin(save, part);
		free(save);
		free(part);
		save = expanded;
		raw++;
	}
	return (expanded);
}
