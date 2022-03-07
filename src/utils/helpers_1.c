/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:43:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 13:07:36 by msousa           ###   ########.fr       */
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
	char *key;

	length = 0;
	if (!ft_isalpha(*raw) && *raw != EXPAND_USCORE)
	{
		raw++;
		length++;
		while (ft_isalnum(*raw) || *raw == EXPAND_USCORE)
		{
			raw++;
			length++;
		}
	}
	if (!length)
		return (ft_strdup(""));
	raw = raw - length;
	key = (char *)malloc(sizeof(char) * (length + 1));
	ft_strlcpy(key, raw, length + 1);
	return (key);
}

char	*get_expanded(char *raw, t_env *env)
{
	char *expanded;
	int	length;
	char *env_key;
	char *env_value;

	// TODO: trim quotes

	expanded = NULL;
	length = 0;
	// only if double quotes or no quotes
	if (*raw == LEXICAL_QUOTE)
		return (ft_strdup(raw));


	while (*raw)
	{
		if (*raw == EXPAND_DOLLAR)
		{
			env_key = find_env_key(raw + 1);

			env_value = get_env(env_key, env);
			free(env_key);

			length += ft_strlen(env_value);
		}
		else
		{
			// ft_putchar(*raw);
			length++;
		}
		raw++;
	}





	// else
	expanded = (char *)malloc(ft_strlen(raw) + 1);
	ft_strcpy(expanded, raw);
	free(raw);
	return (expanded);
}
