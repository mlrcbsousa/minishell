/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:37:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 00:26:23 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_setup_redirect_in(t_io *io)
{
	int	fd;

	fd = open(io->data, O_RDONLY);
	if (fd == -1)
	{
		perror(io->data);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDIN_FILENO);
}

// TODO: not sure, test more
void	run_setup_heredoc(t_io *io, t_app *self)
{
	char	*line;
	char	*expanded;
	int		pipe_fd[2];
	int		read_fd;
	int		write_fd;

	pipe(pipe_fd);
	read_fd = pipe_fd[0];
	write_fd = pipe_fd[1];
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_streq(line, io->data))
		{
			free(line);
			break ;
		}
		expanded = get_expanded(line, self);
		ft_putendl_fd(expanded, write_fd);
		free(expanded);
		free(line);
	}
	dup2(read_fd, STDIN_FILENO);
	// close(read_fd);
	close(write_fd);
}

void	run_setup_redirect_out(t_io *io)
{
	int	fd;

	fd = open(io->data, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror(io->data);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
}

void	run_setup_append(t_io *io)
{
	int	fd;

	fd = open(io->data, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		perror(io->data);
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
}
