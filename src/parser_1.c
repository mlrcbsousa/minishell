/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 22:56:04 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 18:22:24 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_astree	*command_a(t_parser *parser)
{
	t_astree	*command_node;
	t_astree	*result;
	char* filename;

	// test first token if is a command
	command_node = command(parser);
	if (!command_node)
		return (NULL);

	// test next token if is a redirect operator
	if (!match(LEXICAL_LESSER, NULL, parser))
	{
		astree_destroy(command_node);
		return (NULL);
	}

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_destroy(command_node);
		return (NULL);
	}

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_REDIRECT_IN);
	astree_set_data(result, filename);
	astree_add_branches(result, NULL, command_node);
	return (result);
}

t_astree	*command_b(t_parser *parser)
{
	t_astree	*command_node;
	t_astree	*result;
	char* filename;

	// test first token if is a command
	command_node = command(parser);
	if (!command_node)
		return (NULL);

	// test next token if is a redirect operator
	if (!match(LEXICAL_GREATER, NULL, parser))
	{
		astree_destroy(command_node);
		return (NULL);
	}

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_destroy(command_node);
		return (NULL);
	}

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_REDIRECT_OUT);
	astree_set_data(result, filename);
	astree_add_branches(result, NULL, command_node);
	return (result);
}

t_astree	*command_c(t_parser *parser)
{
	t_astree	*command_node;
	t_astree	*result;
	char* delimiter;

	// test first token if is a command
	command_node = command(parser);
	if (!command_node)
		return (NULL);

	// test next token if is a redirect operator
	if (!match(LEXICAL_LLESSER, NULL, parser))
	{
		astree_destroy(command_node);
		return (NULL);
	}

	// test next token if is a default and save delimiter
	if (!match(LEXICAL_DEFAULT, &delimiter, parser))
	{
		free(delimiter);
		astree_destroy(command_node);
		return (NULL);
	}

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_HEREDOC);
	astree_set_data(result, delimiter);
	astree_add_branches(result, NULL, command_node);
	return (result);
}

t_astree	*command_d(t_parser *parser)
{
	t_astree	*command_node;
	t_astree	*result;
	char* filename;

	// test first token if is a command
	command_node = command(parser);
	if (!command_node)
		return (NULL);

	// test next token if is a redirect operator
	if (!match(LEXICAL_GGREATER, NULL, parser))
	{
		astree_destroy(command_node);
		return (NULL);
	}

	// test next token if is a default and save filename
	if (!match(LEXICAL_DEFAULT, &filename, parser))
	{
		free(filename);
		astree_destroy(command_node);
		return (NULL);
	}

	// Create node return it
	result = (t_astree *)malloc(sizeof(t_astree));
	astree_set_type(result, NODE_APPEND);
	astree_set_data(result, filename);
	astree_add_branches(result, NULL, command_node);
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
