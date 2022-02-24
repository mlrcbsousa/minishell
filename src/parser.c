/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:37:24 by msousa            #+#    #+#             */
/*   Updated: 2022/02/24 20:47:22 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree* command_line();			// test all command line composition in order
t_astree* command_line_a();		// <command> '|' <command line>
t_astree* command_line_b();		// <command>

t_astree* command();					// test all command composition in order
t_astree* command_a();				//	<simple command> '<' <filename>
t_astree* command_b();				//	<simple command> '>' <filename>
// t_astree* command_c();				//	<simple command> '<<' <filename>
// t_astree* command_d();				//	<simple command> '>>' <filename>
t_astree* command_e();				//	<simple command>

t_astree* simple_command();		// test simple command composition
t_astree* simple_command_a();	// <cmd_path> <token list>

t_astree* token_list();				// test tokenlist composition
t_astree* token_list_a();			// <token> <token list>
t_astree* token_list_b();			// EMPTY

// Making this a struct for now because don't know if will need more
// info to pass around for these functions
typedef struct s_parser
{
	t_token	*current_token;
} t_parser;

int parse(t_stack *analysed, t_astree **syntax_astree)
{
	t_parser	parser;

	if (!analysed->size)
		return (-1);

	parser.current_token = analysed->token;
	*syntax_astree = simple_command(&parser);

	// If command filter didn't reach the end of the token list
	if (parser.current_token && parser.current_token->type)
	{
		printf("Syntax Error at: %s\n", parser.current_token->data);
		return (-1);
	}
	return (0);
}

// Utility function that checks the current token against the given type
//			and moves the current token to the next on the list either way
// If the types match it returns TRUE
// If the types match and a buffer argument was supplied, current token data
//			is also copied over
// Otherwise returns FALSE
t_bool	match(int token_type, char **buffer, t_parser *parser)
{
	t_token	*token;

	token = parser->current_token;
	if (token == NULL)
		return (FALSE);

	if (token->type == token_type)
	{
		if (buffer)
		{
			*buffer = (char*)malloc(ft_strlen(token->data) + 1);
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
	t_token *save;
	t_astree *node;

	save = parser->current_token;
	node = command_line_a(parser);
	parser->current_token = save;
	if (node)
		return (node);
	node = command_line_b(parser);
	parser->current_token = save;
	if (node)
		return (node);
	return (NULL);
}

t_astree	*command_line_a(t_parser *parser)
{
	t_astree *command_node;
	t_astree *command_line_node;
	t_astree *result;

	command_node = NULL;//command(parser);
	if (!command_node)
		return (NULL);

	if (!match(LEXICAL_PIPE, NULL, parser)) {
		astree_delete(command_node);
		return (NULL);
	}

	command_line_node = command_line(parser);
	if (!command_node)
	{
		astree_delete(command_node);
		return (NULL);
	}
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_PIPE);
	astree_add_branches(result, command_node, command_line_node);
	return result;
}

t_astree	*command_line_b(t_parser *parser)
{
	(void)parser;
	return (NULL);
}

t_astree	*simple_command(t_parser *parser)
{
    t_token	*save;
		save = parser->current_token; // seems useless
    return simple_command_a(parser);
}

t_astree	*simple_command_a(t_parser *parser)
{
	t_astree	*token_list_node;
	t_astree	*result;
	char	*cmd_path;

	if (!match(LEXICAL_DEFAULT, &cmd_path, parser))
			return (NULL);
	token_list_node = token_list(parser);
	// we don't check whether token_list_node is NULL since its allowed to be
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_CMDPATH);
	astree_set_data(result, cmd_path);
	astree_add_branches(result, NULL, token_list_node);
	return (result);
}

t_astree	*token_list(t_parser *parser)
{
	t_token *save;
	t_astree *node;

	save = parser->current_token;
	node = token_list_a(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = token_list_b(parser);
	if (node)
		return (node);
	parser->current_token = save;
	return (NULL);
}

t_astree	*token_list_a(t_parser *parser)
{
	t_astree	*token_list_node;
	t_astree	*result;
	char* arg;

	if (!match(LEXICAL_DEFAULT, &arg, parser))
			return (NULL);
	token_list_node = token_list(parser);
	// we don't check whether token_list_node is NULL since its allowed to be
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_ARGUMENT);
	astree_set_data(result, arg);
	astree_add_branches(result, NULL, token_list_node);
	return (result);
}

t_astree	*token_list_b(t_parser *parser)
{
	(void)parser;
	return (NULL);
}

