/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:43:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 16:37:27 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	should_expand(char *raw)
{
	t_bool	dquote;

	dquote = FALSE;
	if (*raw == LEXICAL_DQUOTE)
		dquote = TRUE;
	if (*raw == LEXICAL_QUOTE)
		return (FALSE);
	while (*raw)
		raw++;
	if (dquote && *(raw - 1) != LEXICAL_DQUOTE)
		return (FALSE);
	return (TRUE);
}

// TODO: not if just open double quote
char	*get_expanded(char *raw, t_app *self)
{
	char	*expanded;
	char	*save;
	char	*part;
	char	*env_key;

	save = ft_strdup("");
	if (!should_expand(raw))
		return (ft_strdup(raw));
	while (*raw)
	{
		if (*raw == EXPAND_DOLLAR && *(raw + 1) == EXPAND_QUESTION)
		{
			part = ft_itoa(g_status.value);
			raw++;
		}
		else if (*raw == EXPAND_DOLLAR
			&& (ft_isalnum(*(raw + 1)) || *(raw + 1) == EXPAND_USCORE))
		{
			env_key = find_env_key(raw + 1);
			part = get_env(env_key, self->env);
			if (!part)
			{
				free(env_key);
				return (save);
			}
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

char	*get_stripped(char *src)
{
	int		length;
	char	quote;

	length = ft_strlen(src);
	if (!length)
		return (ft_strdup(""));
	if (*src != LEXICAL_QUOTE && *src != LEXICAL_DQUOTE)
		return (ft_strdup(src));
	quote = *src;
	while (*src)
		src++;
	if (quote == *(--src))
		return (ft_substr(src - length + 1, 1, length - 2));
	return (ft_strdup(src - length + 1));
}
