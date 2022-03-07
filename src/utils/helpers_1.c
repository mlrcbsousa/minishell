/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:43:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 15:23:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_streq(env->key, key))
		{
			// key doesnt have value
			// TODO: return empty string (which should be env->value)
			if (!ft_strlen(env->value))
				printf("empty string\n");
			return (env->value);
		}
		env = env->next;
	}
	// key doesnt exist
	// check if use ft_strdup("");
	return (NULL);
}

// t_bool	is_valid_identifier(char *str)
// {
// 	int	i;

// 	if(!str)
// 		return (FALSE);

// 	if (!ft_isalpha(str[0]) && str[0] != '_')
// 		return (FALSE);
// 	i = 1;
// 	while (str[i])
// 	{
// 		if (!ft_isalnum(str[i]) && str[i] != '_')
// 			return (FALSE);
// 		i++;
// 	}
// 	return (TRUE);
// }

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
	int	length;
	char *env_key;
	char *env_value;

	// TODO: trim quotes

	expanded = NULL;
	env_value = NULL;
	save = ft_strdup("");

	// only if double quotes or no quotes
	// TODO: not if just open double quote
	if (*raw == LEXICAL_QUOTE)
		return (ft_strdup(raw));

	length = 0;
	while (*raw)
	{
		// enter when valid to find a var key
		if (*raw == EXPAND_DOLLAR)
			// && (ft_isalnum(*(raw + 1))
			// 	|| *(raw + 1) == EXPAND_USCORE
			// 	|| *(raw + 1) == EXPAND_QUESTION))
		{
			if (*(raw + 1) == EXPAND_QUESTION)
			{
				part = ft_itoa(g_return);
				raw = raw + 2;

				printf("env_value: %s\n", env_value);

				expanded = ft_strjoin(save, part);
				free(save);
				free(part);
				save = expanded;
			}
			else if (ft_isalnum(*(raw + 1)) || *(raw + 1) == EXPAND_USCORE)
			{
				env_key = find_env_key(raw + 1);
				env_value = get_env(env_key, env);

				printf("env_key: %s\n", env_key);
				printf("env_value: %s\n", env_value);

				raw = raw + 1 + ft_strlen(env_key);
				free(env_key);
			}
		}
		else
		{
			part = ft_substr(raw, 0, 1);

			expanded = ft_strjoin(save, part);
			free(save);
			free(part);
			save = expanded;
			raw++;
		}
	}
	return (expanded);
}
