/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:07:59 by msousa            #+#    #+#             */
/*   Updated: 2022/02/22 21:17:24 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void astree_add_branches(t_astree *root , t_astree *left , t_astree *right)
{
	if(!root)
		return ;
	root->left = left;
	root->right = right;
}

void astree_set_type(t_astree *node , t_node type)
{
	if(!node)
		return ;
	node->type = type;
}

void astree_set_data(t_astree *node , char *data)
{
	if(!node)
		return ;
	if(data)
	{
		node->data = data;
		node->type = NODE_DATA;
  }
}

void astree_delete(t_astree *node)
{
	if (node == NULL)
		return;
	if (node->type == NODE_DATA)
		free(node->data);
	astree_delete(node->left);
	astree_delete(node->right);
	free(node);
}
