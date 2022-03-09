/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:07:59 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 15:14:42 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	astree_add_branches(t_astree *root, t_astree *left, t_astree *right)
{
	if (!root)
		return ;
	root->left = left;
	root->right = right;
}

void	astree_set_type(t_astree *node, t_node type)
{
	if (!node)
		return ;
	node->type = type;
}

void	astree_set_data(t_astree *node, char *data)
{
	if (!node || !data)
		return ;
	node->data = data;
	if (!node->type)
		node->type = NODE_DATA;
}

void	astree_destroy(t_astree *node)
{
	if (!node)
		return ;
	if (node->data)
		free(node->data);
	astree_destroy(node->left);
	astree_destroy(node->right);
	free(node);
}
