/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:19:41 by msousa            #+#    #+#             */
/*   Updated: 2022/02/28 20:52:07 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void execute_simple_command(t_astree *simple_command_node,
																	t_executor executor)
{
	t_command command;

	init_command(simple_command_node, &command, executor);
	execute_command(&command);
	destroy_command(&command);
}

static void execute_command_line(t_astree *node, t_executor executor)
{
	if (!node)
		return ;
	if (node->type == NODE_REDIRECT_IN)
	{
		executor.redirect_in = node->data;
		// right node has command information
		execute_simple_command(node->right, executor);
	}
	else if (node->type == NODE_REDIRECT_OUT)
	{
		executor.redirect_out = node->data;
		// right node has command information
		execute_simple_command(node->right, executor);
	}
	else if (node->type == NODE_CMDPATH)
		// current node has command information
		execute_simple_command(node, executor);
}

// pipe() is a Linux system function. The pipe() system function is used to open
// file descriptors, which are used to communicate between different Linux
// processes. In short, the pipe() function is used for inter-process
// communication in Linux.
//
// https://linuxhint.com/pipe_system_call_c/#:~:text=pipe()%20is%20a%20Linux,inter%2Dprocess%20communication%20in%20Linux.
// `man 2 pipe`
static void execute_pipeline(t_astree *pipe_node)
{
	int pipe_fd[2];
	int read_fd;
	int write_fd;
	t_astree *node;

	pipe(pipe_fd);
	read_fd = pipe_fd[0];
	write_fd = pipe_fd[1];

	// read from stdin for the pipe start
	// this is from the left node of the pipe node as seen in parser
	execute_command_line(pipe_node->left,
											(t_executor){FALSE, TRUE, 0, write_fd, NULL, NULL});
	node = pipe_node->right;
	// loop the pipe_nodes
	while (node && node->type == NODE_PIPE)
	{
		// close the write fd
		close(write_fd);
		pipe(pipe_fd);
		// get a new write fd
		write_fd = pipe_fd[1];

		// this is from the left node of the pipe node as seen in parser
		execute_command_line(node->left,
											(t_executor){TRUE, TRUE, read_fd, write_fd, NULL, NULL});
		// close the write fd
		close(read_fd);
		// get the new read fd
		read_fd = pipe_fd[0];

		node = node->right;
	}
	// close the write fd
	read_fd = pipe_fd[0];
	close(write_fd);

	// write output to stdout for the pipe end
	execute_command_line(node,
											(t_executor){TRUE, FALSE, read_fd, 0, NULL, NULL});
	// close the read fd
	close(read_fd);
}

void execute(t_astree *node)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
		execute_pipeline(node);
	else
		execute_command_line(node, (t_executor){FALSE, FALSE, 0, 0, NULL, NULL});
}
