/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 02:30:13 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 02:30:45 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_setup_io_in(t_io *io, t_app *self)
{
	while (io)
	{
		if (io->type == NODE_REDIRECT_IN)
			run_setup_redirect_in(io);
		if (io->type == NODE_HEREDOC)
			run_setup_heredoc(io, self);
		io = io->next;
	}
}

void	run_setup_io_out(t_io *io)
{
	while (io)
	{
		if (io->type == NODE_REDIRECT_OUT)
			run_setup_redirect_out(io);
		if (io->type == NODE_APPEND)
			run_setup_append(io);
		io = io->next;
	}
}

void	run_setup_io(t_command *command, t_app *self)
{
	if (command->redirect_in)
		run_setup_io_in(command->redirect_in, self);
	if (command->redirect_out)
		run_setup_io_out(command->redirect_out);
	if (command->stdin_pipe)
		dup2(command->pipe_read, STDIN_FILENO);
	if (command->stdout_pipe)
		dup2(command->pipe_write, STDOUT_FILENO);
}
