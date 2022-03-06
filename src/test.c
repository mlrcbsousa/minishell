/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:21:16 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 15:23:26 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test tree contents
void print_astree(t_astree *node)
{
	if (!node)
		return;
	printf("\n--Node--\n");
	printf("type: %d\n", node->type);
	printf("data: %s\n", node->data);
	print_astree(node->left);
	print_astree(node->right);
}

// Test tokens contents
void print_tokens(t_token *token)
{
	if (!token)
		return;
	while (token)
	{
		printf("\n--Token--\n");
		printf("type: %d\n", token->type);
		printf("data: %s\n", token->data);
		token = token->next;
	}
}

// TEST - print command info
void print_command(t_command *command)
{
	printf("\n--Command--\n");
	printf("args: ");
	int i = 0;
	while (i < command->argc)
		printf("%s ", command->argv[i++]);
	printf("\n");
	printf("stdin_pipe: %d\n", command->stdin_pipe);
	printf("stdout_pipe: %d\n", command->stdout_pipe);
	printf("pipe_read: %d\n", command->pipe_read);
	printf("pipe_write: %d\n", command->pipe_write);
	printf("redirect_in: %s\n", command->redirect_in);
	printf("redirect_out: %s\n", command->redirect_out);
	printf("\n");
}
