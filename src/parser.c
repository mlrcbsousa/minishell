/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:37:24 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 18:02:55 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**

<command line>   ::=  <command> '|' <command line>
                  |   <command>

<command>        ::=  <simple command> '<' <filename>
                  |   <simple command> '>' <filename>
                  |   <simple command>

<simple command> ::=  <cmd path> <token list>

<token list>     ::=  <token> <token list>
                  |   (EMPTY)

**/

// t_astree* command_line();     // test "command line" possibilities
// t_astree* command_line_a();   // <command> '|' <command line>
//                               // <command>

// t_astree* command();          // test "command" possibilities
// t_astree* command_a();        // <simple command> '<' <filename>
// t_astree* command_b();        // <simple command> '>' <filename>
// t_astree* command_c();        // <simple command> '<<' <filename>
// t_astree* command_d();        // <simple command> '>>' <filename>
//                               // <simple command>

//                               // test "simple command" possibilities
// t_astree* simple_command();   // <command path> <token list>

// t_astree* token_list();       // test "token list" possibilities
// t_astree* token_list_a();     // <token> <token list>
//                               // EMPTY

// Making this a struct for now because don't know if will need more
// info to pass around for these functions
int	parse(t_stack *analysed, t_astree **astree)
{
	t_parser	parser;

	if (!analysed->size)
		return (-1);
	parser.current_token = analysed->token;
	*astree = command_line(&parser);
	if (parser.current_token && parser.current_token->type)
	{
		printf("Syntax Error at: %s\n", parser.current_token->data);
		return (-1);
	}
	return (0);
}

t_bool	match(int token_type, char **buffer, t_parser *parser)
{
	t_token	*token;

	token = parser->current_token;
	if (!token)
		return (FALSE);
	if (token->type == token_type)
	{
		if (buffer)
		{
			*buffer = (char *)malloc(ft_strlen(token->data) + 1);
			ft_strcpy(*buffer, token->data);
		}
		parser->current_token = token->next;
		return (TRUE);
	}
	parser->current_token = token->next;
	return (FALSE);
}

t_astree	*command_line(t_parser *parser)
{
	t_token		*save;
	t_astree	*node;

	save = parser->current_token;
	node = command_line_a(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = command(parser);
	if (node)
		return (node);
	parser->current_token = save;
	return (NULL);
}

t_astree	*command_line_a(t_parser *parser)
{
	t_astree	*command_node;
	t_astree	*command_line_node;
	t_astree	*result;

	command_node = command(parser);
	if (!command_node)
		return (NULL);
	if (!match(LEXICAL_PIPE, NULL, parser))
	{
		astree_destroy(command_node);
		return (NULL);
	}
	command_line_node = command_line(parser);
	if (!command_node)
	{
		astree_destroy(command_node);
		return (NULL);
	}
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_PIPE);
	astree_add_branches(result, command_node, command_line_node);
	return (result);
}

t_astree	*command(t_parser *parser)
{
	t_token		*save;
	t_astree	*node;

	save = parser->current_token;
	node = command_a(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = command_b(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = command_c(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = command_d(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = simple_command(parser);
	if (node)
		return (node);
	parser->current_token = save;
	return (NULL);
}
