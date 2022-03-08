/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:21:16 by msousa            #+#    #+#             */
/*   Updated: 2022/03/08 13:26:52 by msousa           ###   ########.fr       */
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

// Test redirects contents
void print_ios(t_io *io)
{
	if (!io)
		return;
	while (io)
	{
		printf("IO: type: %d, data: %s, ", io->type, io->data);
		io = io->next;
	}
	printf("\n");
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
	printf("redirect_in: ");
	print_ios(command->redirect_in);
	printf("\n");
	printf("redirect_out: ");
	print_ios(command->redirect_out);
	printf("\n");
}
