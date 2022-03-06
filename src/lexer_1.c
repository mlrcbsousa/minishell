/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:52:15 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 16:16:37 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_end_read_token(t_lexer *lexer)
{
	if (lexer->data_i > 0)
	{
		// end previous token data
		lexer->token->data[lexer->data_i] = 0;
		lexer->token->next = (t_token *)malloc(sizeof(t_token));
		lexer->token = lexer->token->next;
		// make new token data size smaller by how far along in line size
		token_init(lexer->token, lexer->size - lexer->line_i);
		// reset token data index
		lexer->data_i = 0;
	}
}

// if quotes or double quotes create grouping using state change
void	lexer_type_quote(t_lexer *lexer)
{
	lexer->state = STATE_QUOTE;
	lexer->token->data[lexer->data_i++] = LEXICAL_QUOTE;
	lexer->token->type = LEXICAL_DEFAULT;
}

// If quote or double quote change state
void	lexer_type_dquote(t_lexer *lexer)
{
	lexer->state = STATE_DQUOTE;
	lexer->token->data[lexer->data_i++] = LEXICAL_DQUOTE;
	// since not operator token use default type
	lexer->token->type = LEXICAL_DEFAULT;
}

void	lexer_type_default(t_lexer *lexer)
{
	lexer->token->data[lexer->data_i++] = lexer->c;
	lexer->token->type = LEXICAL_DEFAULT;
}

void	lexer_type_operator(t_lexer *lexer)
{
	// if token data already has something split off and start new token
	lexer_end_read_token(lexer);

	lexer->token->data[0] = lexer->type;

	// handle double redirects
	if (lexer->type == LEXICAL_GREATER
		&& lexer->line[lexer->line_i + 1] == LEXICAL_GREATER)
	{
		lexer->token->data[1] = lexer->type;
		lexer->token->data[2] = 0;
		lexer->type = LEXICAL_GGREATER;
		lexer->line_i++;
	}
	else if (lexer->type == LEXICAL_LESSER
		&& lexer->line[lexer->line_i + 1] == LEXICAL_LESSER)
	{
		lexer->token->data[1] = lexer->type;
		lexer->token->data[2] = 0;
		lexer->type = LEXICAL_LLESSER;
		lexer->line_i++;
	}
	else
		lexer->token->data[1] = 0;

	lexer->token->type = lexer->type;

	// when operator token need an additional token created
	lexer->token->next = (t_token *)malloc(sizeof(t_token));
	lexer->token = lexer->token->next;
	token_init(lexer->token, lexer->size - lexer->line_i);
}
