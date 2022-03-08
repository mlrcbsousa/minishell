/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:43:03 by msousa            #+#    #+#             */
/*   Updated: 2022/03/08 18:33:56 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_expand(t_token *token, t_env *env)
{
	char *expanded;
	char *stripped;

	while (token)
	{
		if (token->type == LEXICAL_DEFAULT)
		{
			expanded = get_expanded(token->data, env);
			stripped = get_stripped(expanded);
			free(expanded);
			free(token->data);
			token->data = stripped;
		}
		token = token->next;
	}
}
