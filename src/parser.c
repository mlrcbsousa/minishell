/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:37:24 by msousa            #+#    #+#             */
/*   Updated: 2022/02/24 22:40:36 by msousa           ###   ########.fr       */
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

t_astree* command_line();     // test "command line" possibilities
t_astree* command_line_a();   // <command> '|' <command line>
// t_astree* command_line_b();   // <command>

t_astree* command();          // test "command" possibilities
t_astree* command_a();        // <simple command> '<' <filename>
t_astree* command_b();        // <simple command> '>' <filename>
// t_astree* command_c();     // <simple command> '<<' <filename>
// t_astree* command_d();     // <simple command> '>>' <filename>
// t_astree* command_c();        // <simple command>

// t_astree* simple_command();// test "simple command" possibilities
t_astree* simple_command();   // <command path> <token list>

// t_astree* token_list();    // test "token list" possibilities
t_astree* token_list();       // <token> <token list>
// no function //             // EMPTY (implicit)

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
	*syntax_astree = command(&parser);

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
	t_astree *command_node;
	t_astree *command_line_node;
	t_astree *result;

	// test first token if is a command
	command_node = command(parser);
	if (!command_node)
		return (NULL);

	// test next token if is a pipe operator
	if (!match(LEXICAL_PIPE, NULL, parser))
	{
		astree_delete(command_node);
		return (NULL);
	}

	// test next token if is a command line
	command_line_node = command_line(parser);
	if (!command_node)
	{
		astree_delete(command_node);
		return (NULL);
	}
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_PIPE);
	astree_add_branches(result, command_node, command_line_node);
	return (result);
}

t_astree	*command(t_parser *parser)
{
	t_token	*save;
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
	node = simple_command(parser);
	if (node)
		return (node);
	parser->current_token = save;
	return (NULL);
}

t_astree	*command_a(t_parser *parser)
{
	t_astree	*simple_command_node;
	t_astree	*result;
	char* filename;

	// test first token if is a simple command
	simple_command_node = simple_command(parser);
	if (!simple_command_node)
		return (NULL);

	// test next token if is a redirect operator
	if (!match(LEXICAL_LESSER, NULL, parser))
	{
		astree_delete(simple_command_node);
		return (NULL);
	}

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_delete(simple_command_node);
		return (NULL);
	}

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_REDIRECT_IN);
	astree_set_data(result, filename);
	astree_add_branches(result, NULL, simple_command_node);
	return (result);
}

t_astree	*command_b(t_parser *parser)
{
	t_astree	*simple_command_node;
	t_astree	*result;
	char* filename;

	// test first token if is a simple command
	simple_command_node = simple_command(parser);
	if (!simple_command_node)
		return (NULL);

	// test next token if is a redirect operator
	printf("GET HERE\n");

	if (!match(LEXICAL_GREATER, NULL, parser))
	{
		astree_delete(simple_command_node);
		return (NULL);
	}
	printf("GET HERE\n");

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_delete(simple_command_node);
		return (NULL);
	}

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_REDIRECT_OUT);
	astree_set_data(result, filename);
	astree_add_branches(result, NULL, simple_command_node);
	return (result);
}

t_astree	*simple_command(t_parser *parser)
{
	t_astree	*token_list_node;
	t_astree	*result;
	char	*command_path;

	if (!match(LEXICAL_DEFAULT, &command_path, parser))
			return (NULL);
	token_list_node = token_list(parser);
	// we don't check whether token_list_node is NULL since its allowed to be
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_CMDPATH);
	astree_set_data(result, command_path);
	astree_add_branches(result, NULL, token_list_node);
	return (result);
}

// Is this wrapper needed?
// t_astree	*token_list(t_parser *parser)
// {
// 	t_token *save;
// 	t_astree *node;

// 	save = parser->current_token;
// 	node = token_list_a(parser);
// 	if (node)
// 		return (node);
// 	parser->current_token = save;
// 	return (NULL);
// }

t_astree	*token_list(t_parser *parser)
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
