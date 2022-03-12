/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:43:03 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 10:36:45 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_expand(t_token *token, t_app *self)
{
	char	*expanded;
	char	*stripped;
	t_token	*previous;

	previous = token;
	while (token)
	{
		if (token->type == LEXICAL_DEFAULT)
		{
			expanded = get_expanded(token->data, self);
			stripped = get_stripped(expanded);
			free(expanded);
			free(token->data);
			token->data = stripped;
			printf("DEBUG: lexer_expand\n");
			printf("DEBUG: stripped: %s\n", stripped);
			printf("DEBUG: ft_strlen(stripped): %zu\n", ft_strlen(stripped));
			if (!ft_strlen(stripped))
			{
				free(token->data);
				if (token == previous)
				{
					token = token->next;
					free(previous);
					previous = token;
				}
				else
				{
					previous->next = token->next;
					free(token);
					token = previous->next;
				}
				continue ;
			}

		}
		previous = token;
		token = token->next;
	}
}
