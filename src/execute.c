/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:19:41 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 17:48:21 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TEST
// print_command(&command);
static void	execute_simple_command(t_astree *simple_command_node,
	t_executor executor, t_app *self)
{
	t_command	command;

	command = (t_command){0, NULL, FALSE, FALSE, 0, 0, 0, 0};
	command_init(simple_command_node, &command, executor);
	command_execute(&command, self);
	command_destroy(&command);
}

// recursively add chain of redirects
static void	execute_redirect_command(t_astree *node, t_executor *executor)
{
	t_io	*io;

	if (!node)
		return ;
	io = (t_io *)malloc(sizeof(t_io));
	io->next = NULL;
	io->type = node->type;
	io->data = ft_strdup(node->data);
	if (node->type == NODE_REDIRECT_IN)
		redirect_add_back(&executor->redirect_in, io);
	else if (node->type == NODE_HEREDOC)
		redirect_add_back(&executor->redirect_in, io);
	else if (node->type == NODE_REDIRECT_OUT)
		redirect_add_back(&executor->redirect_out, io);
	else if (node->type == NODE_APPEND)
		redirect_add_back(&executor->redirect_out, io);
	execute_redirect_command(node->left, executor);
}

static void	execute_command_line(t_astree *node, t_executor executor,
	t_app *self)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIRECT_IN
		|| node->type == NODE_REDIRECT_OUT
		|| node->type == NODE_HEREDOC
		|| node->type == NODE_APPEND)
	{
		execute_redirect_command(node, &executor);
		execute_simple_command(node->right, executor, self);
	}
	else if (node->type == NODE_CMDPATH)
		execute_simple_command(node, executor, self);
}

static void	execute_pipeline(t_astree *pipe_node, t_app *self)
{
	int			pipe_fd[2];
	int			read_fd;
	int			write_fd;
	t_astree	*node;

	pipe(pipe_fd);
	read_fd = pipe_fd[0];
	write_fd = pipe_fd[1];
	execute_command_line(pipe_node->left,
		(t_executor){FALSE, TRUE, 0, write_fd, 0, 0}, self);
	node = pipe_node->right;
	while (node && node->type == NODE_PIPE)
	{
		close(write_fd);
		pipe(pipe_fd);
		write_fd = pipe_fd[1];
		execute_command_line(node->left,
			(t_executor){TRUE, TRUE, read_fd, write_fd, 0, 0}, self);
		close(read_fd);
		read_fd = pipe_fd[0];
		node = node->right;
	}
	read_fd = pipe_fd[0];
	close(write_fd);
	execute_command_line(node, (t_executor){TRUE, FALSE, read_fd, 0, 0, 0},
		self);
	close(read_fd);
}

void	execute_tree(t_astree *node, t_app *self)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipeline(node, self);
	else
		execute_command_line(node, (t_executor){FALSE, FALSE, 0, 0, 0, 0},
			self);
}
