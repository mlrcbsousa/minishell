/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:52:15 by msousa            #+#    #+#             */
/*   Updated: 2022/02/21 21:18:51 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_lexer
{
	int state;
	char *line;
	int size;
	int line_i;
	int data_i;
	char c;
	int type;
} t_lexer;

t_bool is_token_type_operator(char type)
{
	return (type == LEXICAL_SEMICOLON
		|| type == LEXICAL_GREATER
		|| type == LEXICAL_LESSER
		|| type == LEXICAL_PIPE);
}

t_bool is_token_type_grouping(char type)
{
	return (type == LEXICAL_QUOTE
		|| type == LEXICAL_DQUOTE
		|| type == LEXICAL_ESCAPESEQUENCE
		|| type == LEXICAL_DEFAULT);
}

void lexical_analysis_type_grouping(t_token *token, t_lexer *lexer)
{
	// If quote or double quote change state
	if (lexer->type == LEXICAL_QUOTE)
		lexer->state = STATE_QUOTE;
	else if (lexer->type == LEXICAL_DQUOTE)
		lexer->state = STATE_DQUOTE;

	// if escape character copy the character after current into token data
	// will probably need to build this out more
	if (lexer->type == LEXICAL_ESCAPESEQUENCE)
		token->data[lexer->data_i++] = lexer->line[++lexer->line_i];
	else
		token->data[lexer->data_i++] = lexer->c;

	// since not operator token use default type
	token->type = LEXICAL_DEFAULT;
}

// if quotes or double quotes create grouping using state change
// while going through line check for various contextual grammar
// if operator (pipe, redirect or semi-colon) create new token
void lexical_analysis_type(t_token *token, t_lexer *lexer)
{
	if (is_token_type_grouping(lexer->type))
		lexical_analysis_type_grouping(token, lexer);
	else if (is_token_type_operator(lexer->type)
		|| lexer->type == LEXICAL_WHITESPACE)
	{
		// if token data already has something split off and start new token
		if (lexer->data_i > 0)
		{
			// end previous token data
			token->data[lexer->data_i] = 0;

			token->next = (t_token *)malloc(sizeof(t_token));
			token = token->next;

			// make new token data size smaller by how far along in line size
			token_init(token, lexer->size - lexer->data_i);

			// reset token data index
			lexer->data_i = 0;
		}

		// when operator token need an additional token created
		if (is_token_type_operator(lexer->type))
		{
			// add next token
			token->data[0] = lexer->type;
			token->data[1] = 0;
			token->type = lexer->type;

			token->next = (t_token *)malloc(sizeof(t_token));
			token = token->next;
			token_init(token, lexer->size - lexer->data_i);
		}
	}
}

void	lexical_analysis_state(t_token *token, char *line, int size)
{
	t_lexer	lexer;

	lexer = (t_lexer){STATE_DEFAULT, line, size, 0, 0, 0, 0};
	while (line[lexer.line_i])
	{
		lexer.c = line[lexer.line_i];
		lexer.type = lexical_type(lexer.c);

		if (lexer.state == STATE_DEFAULT)
			lexical_analysis_type(token, &lexer);
		else if (lexer.state == STATE_DQUOTE || lexer.state == STATE_QUOTE)
		{
			token->data[lexer.data_i++] = lexer.c;

			// if closing quote
			if ((lexer.type == LEXICAL_DQUOTE && lexer.state == STATE_DQUOTE)
				|| (lexer.type == LEXICAL_QUOTE && lexer.state == STATE_QUOTE))
				// exit quote grouping
				lexer.state = STATE_DEFAULT;
		}

		// if needed, close data and reset data index
		if (lexer.type == LEXICAL_NULL && lexer.data_i > 0)
		{
			token->data[lexer.data_i] = 0;
			lexer.data_i = 0;
		}

		lexer.line_i++;
	}
}

// To do
// void	strip_quotes(char *src, char *dest)
// {
// 	(void)src;
// 	(void)dest;
// }

void	lexical_analysis(char *line, size_t size, t_stack *analysed)
{
	t_token *token;
	// char *stripped;

	if (!size)
		return ;
	analysed->token = (t_token *)malloc(sizeof(t_token));
	token = analysed->token;
	token_init(token, size);
	lexical_analysis_state(token, line, size);

	// count default tokens and strip quotes
	while (token)
	{
		if (token->type == LEXICAL_DEFAULT)
		{
			// might be inside quotation to escape special characters
			// stripped = (char *)malloc(ft_strlen(token->data) + 1);
			// strip_quotes(token->data, stripped);
			// free(token->data);
			// token->data = stripped;
			analysed->size++;
		}
		token = token->next;
	}
}
