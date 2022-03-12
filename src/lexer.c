/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:52:15 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 15:08:47 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_state_default(t_lexer *lexer)
{
	if (lexer->type == LEXICAL_QUOTE)
		lexer_type_quote(lexer);
	else if (lexer->type == LEXICAL_DQUOTE)
		lexer_type_dquote(lexer);
	else if (lexer->type == LEXICAL_DEFAULT)
		lexer_type_default(lexer);
	else if (lexer->type == LEXICAL_WHITESPACE)
		lexer_end_read_token(lexer);
	else if (lexer->type == LEXICAL_GREATER
		|| lexer->type == LEXICAL_LESSER
		|| lexer->type == LEXICAL_PIPE)
		lexer_type_operator(lexer);
}

static void	lexer_state_dquote(t_lexer *lexer)
{
	lexer->token->data[lexer->data_i++] = lexer->c;
	if (lexer->type == LEXICAL_DQUOTE)
		lexer->state = STATE_DEFAULT;
}

static void	lexer_state_quote(t_lexer *lexer)
{
	lexer->token->data[lexer->data_i++] = lexer->c;
	if (lexer->type == LEXICAL_QUOTE)
		lexer->state = STATE_DEFAULT;
}

static void	lexical_analysis_char(t_lexer *lexer, char *line)
{
	lexer->c = line[lexer->line_i];
	lexer->type = lexical_type(lexer->c);
	if (lexer->state == STATE_DEFAULT)
		lexer_state_default(lexer);
	else if (lexer->state == STATE_DQUOTE)
		lexer_state_dquote(lexer);
	else if (lexer->state == STATE_QUOTE)
		lexer_state_quote(lexer);
	if (lexer->type == LEXICAL_NULL)
		lexer_type_null(lexer);
		lexer->line_i++;
}

/* while going through line check for various contextual grammar
** first check by state (is inside quotes or not) then type (token type info)
*/
void	lexical_analysis(char *line, int size, t_stack *analysed, t_app *self)
{
	t_lexer	lexer;

	if (!size)
		return ;
	analysed->token = (t_token *)malloc(sizeof(t_token));
	lexer = (t_lexer){analysed->token, STATE_DEFAULT, size, line, 0, 0, 0, 0};
	token_init(lexer.token, lexer.size);
	while (line[lexer.line_i])
		lexical_analysis_char(&lexer, line);
	lexical_analysis_char(&lexer, line);
	lexer_expand(analysed->token, self);
	analysed->size = tokens_length(analysed->token);
}
