/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 22:09:25 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 22:26:49 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree	*redirect_command_a(t_parser *parser)
{
	t_astree	*redirect_node;
	t_astree	*result;
	char* filename;

	// test next token if is a redirect operator
	if (!match(LEXICAL_LESSER, NULL, parser))
		return (NULL);

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		return (NULL);
	}

	redirect_node = redirect_command(parser);

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_REDIRECT_IN);
	astree_set_data(result, filename);
	astree_add_branches(result, redirect_node, NULL);
	return (result);
}

t_astree	*redirect_command_b(t_parser *parser)
{
	t_astree	*redirect_node;
	t_astree	*result;
	char* filename;

	// test next token if is a redirect operator
	if (!match(LEXICAL_GREATER, NULL, parser))
		return (NULL);

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		return (NULL);
	}

	redirect_node = redirect_command(parser);

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_REDIRECT_OUT);
	astree_set_data(result, filename);
	astree_add_branches(result, redirect_node, NULL);
	return (result);
}

t_astree	*redirect_command_c(t_parser *parser)
{
	t_astree	*redirect_node;
	t_astree	*result;
	char* delimiter;

	// test next token if is a redirect operator
	if (!match(LEXICAL_LLESSER, NULL, parser))
		return (NULL);

	// test next token if is a default and save delimiter
	if (!match(LEXICAL_DEFAULT, &delimiter, parser))
	{
		free(delimiter);
		return (NULL);
	}

	redirect_node = redirect_command(parser);

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_HEREDOC);
	astree_set_data(result, delimiter);
	astree_add_branches(result, redirect_node, NULL);
	return (result);
}

t_astree	*redirect_command_d(t_parser *parser)
{
	t_astree	*redirect_node;
	t_astree	*result;
	char* filename;

	// test next token if is a redirect operator
	if (!match(LEXICAL_GGREATER, NULL, parser))
		return (NULL);

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		return (NULL);
	}

	redirect_node = redirect_command(parser);

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_APPEND);
	astree_set_data(result, filename);
	astree_add_branches(result, redirect_node, NULL);
	return (result);
}

t_astree	*redirect_command(t_parser *parser)
{
	t_token	*save;
	t_astree	*node;

	save = parser->current_token;
	node = redirect_command_a(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = redirect_command_b(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = redirect_command_c(parser);
	if (node)
		return (node);
	parser->current_token = save;
	node = redirect_command_d(parser);
	if (node)
		return (node);
	parser->current_token = save;
	return (NULL);
}
