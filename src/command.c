/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:56:15 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 02:44:34 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_node_argument(t_astree *node)
{
	if (!node)
		return (FALSE);
	return (node->type == NODE_ARGUMENT || node->type == NODE_CMDPATH);
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

void	command_init(t_astree *simple_command_node, t_command *command,
									t_executor executor)
{
	int			i;
	t_astree	*node;

	if (!simple_command_node || simple_command_node->type != NODE_CMDPATH)
		return ;
	i = 0;
	node = simple_command_node;
	while (is_node_argument(node))
	{
		node = node->right;
		i++;
	}
	command->argv = (char **)malloc(sizeof(char *) * (i + 1));
	i = 0;
	node = simple_command_node;
	while (is_node_argument(node))
	{
		command->argv[i] = ft_strdup(node->data);
		node = node->right;
		i++;
	}
	command->argv[i] = NULL;
	command->argc = i;
	command_fill(command, executor);
}

void	command_execute(t_command *command, t_app *self)
{
	t_builtin	*builtin;

	if (command->argc < 0)
		return ;
	builtin = get_builtin(*command->argv);
	if (builtin)
		self->status = builtin(command, self);
	else
		run(command, self);
}

void	command_destroy(t_command *command)
{
	int	i;

	i = 0;
	while (i < command->argc)
		free(command->argv[i++]);
	free(command->argv);
	if (command->redirect_in)
		redirect_clear(&command->redirect_in);
	if (command->redirect_out)
		redirect_clear(&command->redirect_out);
	command->argc = 0;
}
