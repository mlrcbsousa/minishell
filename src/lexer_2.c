/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:43:03 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 00:14:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_expand(t_token *token, t_app *self)
{
	char	*expanded;
	char	*stripped;

	while (token)
	{
		if (token->type == LEXICAL_DEFAULT)
		{
			expanded = get_expanded(token->data, self);
			stripped = get_stripped(expanded);
			free(expanded);
			free(token->data);
			token->data = stripped;
		}
		token = token->next;
	}
}
