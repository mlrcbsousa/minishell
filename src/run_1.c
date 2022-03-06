/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:37:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 18:52:02 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_setup_redirect_in(t_command *command)
{
	int fd;

	if (command->redirect_in)
	{
		fd = open(command->redirect_in, O_RDONLY);
		if (fd == -1)
		{
			perror(command->redirect_in);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
	}
}

void	run_setup_heredoc(t_command *command)
{
	int fd;

	if (command->heredoc)
	{
		fd = 0;
	}
}

void	run_setup_redirect_out(t_command *command)
{
	int fd;

	if (command->redirect_out)
	{
		// https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
		fd = open(command->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
									S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			perror(command->redirect_out);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void	run_setup_append(t_command *command)
{
	int fd;

	if (command->append)
	{
		// https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
		fd = open(command->append, O_WRONLY | O_CREAT | O_APPEND,
									S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			perror(command->append);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
	}
}

void	run_setup_pipe_read(t_command *command)
{
	// read from stdin pipe
	if (command->stdin_pipe)
		dup2(command->pipe_read, STDIN_FILENO);
}
