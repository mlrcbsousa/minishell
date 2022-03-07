/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:21:16 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 16:22:08 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
