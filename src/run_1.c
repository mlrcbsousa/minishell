/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:37:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 23:04:52 by msousa           ###   ########.fr       */
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
	char	*line;
	int pipe_fd[2];
	int read_fd;
	int write_fd;

	if (command->heredoc)
	{
		pipe(pipe_fd);
		read_fd = pipe_fd[0];
		write_fd = pipe_fd[1];

		while (1)
		{
			line = readline("> ");
			if (line == NULL)
			{
				// TODO: not sure, test more
				break ;
			}
			if (ft_streq(line, command->heredoc))
			{
				free(line);
				break ;
			}
			// TODO: expand env vars before writing
			ft_putendl_fd(line, write_fd);
			free(line);
		}
		dup2(read_fd, STDIN_FILENO);
		close(read_fd);
		close(write_fd);
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
