/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:37:24 by msousa            #+#    #+#             */
/*   Updated: 2022/02/22 20:28:00 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_node {
	NODE_PIPE					= (1 << 0),
	NODE_BCKGRND 			= (1 << 1),
	NODE_SEQ 					= (1 << 2),
	NODE_REDIRECT_IN 	= (1 << 3),
	NODE_REDIRECT_OUT = (1 << 4),
	NODE_CMDPATH			= (1 << 5),
	NODE_ARGUMENT			= (1 << 6),

	NODE_DATA 				= (1 << 7),
} t_node;

typedef struct s_parser
{
	t_token	*token;
} t_parser;

int parse(t_stack *analysed, t_btree **syntax_tree)
{
	t_parser	parser;

	(void)syntax_tree;
	if (!analysed->size)
		return (-1);

	parser.token = analysed->token;
	// *syntax_tree = command_line();

	// If command filter didn't reach the end of the token list
	if (parser.token && parser.token->type)
	{
		printf("Syntax Error at: %s\n", parser.token->data);
		return (-1);
	}

	return (0);
}
