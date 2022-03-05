/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 22:56:04 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 15:22:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
		astree_destroy(simple_command_node);
		return (NULL);
	}

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_destroy(simple_command_node);
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
	if (!match(LEXICAL_GREATER, NULL, parser))
	{
		astree_destroy(simple_command_node);
		return (NULL);
	}

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_destroy(simple_command_node);
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

t_astree	*token_list(t_parser *parser)
{
	t_token *save;
	t_astree *node;

	save = parser->current_token;
	node = token_list_a(parser);
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
