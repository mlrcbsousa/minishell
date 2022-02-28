/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:56:15 by msousa            #+#    #+#             */
/*   Updated: 2022/02/28 21:20:26 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_node_argument(t_astree *node)
{
	return (node && (node->type == NODE_ARGUMENT || node->type == NODE_CMDPATH));
}

static void	command_fill(t_command *command, t_executor executor)
{
	command->stdin_pipe = executor.stdin_pipe;
	command->stdout_pipe = executor.stdout_pipe;
	command->pipe_read = executor.pipe_read;
	command->pipe_write = executor.pipe_write;
	command->redirect_in = executor.redirect_in;
	command->redirect_out = executor.redirect_out;
}

void command_init(t_astree *simple_command_node,
									t_command *command,
									t_executor executor)
{
	int i;
	t_astree *node;

	if (!simple_command_node || simple_command_node->type != NODE_CMDPATH)
		return ;
	// count arguments
	i = 0;
	node = simple_command_node;
	while (is_node_argument(node)) {
		node = node->right;
		i++;
	}
	// allocate size of arguments list
	command->argv = (char **)malloc(sizeof(char*) * (i + 1));

	// copy data into string array of arguments
	i = 0;
	node = simple_command_node;
	while (is_node_argument(node)) {
		command->argv[i] = (char *)malloc(ft_strlen(node->data) + 1);
		ft_strcpy(command->argv[i], node->data);
		node = node->right;
		i++;
	}
	// close argv
	command->argv[i] = NULL;
	command->argc = i;
	command_fill(command, executor);
}

void command_execute(t_command *command)
{
	(void)command;
}

void command_destroy(t_command *command)
{
	(void)command;
}