/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 02:21:04 by msousa           ###   ########.fr       */
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

// printf("%s\n", *command->argv);
void	run(t_command *command, t_app *self)
{
	pid_t	pid;
	int		stdout_fd;
	int		status;
	char	*name;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, self->sigint_handler);
		stdout_fd = dup(STDOUT_FILENO);
		run_setup_io(command, self);
		name = command->argv[0];
		find_binary_path(command, self->env);
		if (execve(*command->argv, command->argv, get_env_raw(self)) == -1)
		{
			dup2(stdout_fd, STDOUT_FILENO);
			if (errno == ENOENT)
			{
				if ((*name == '.' && *(name + 1) == '/') || *name == '/')
					print_errno(name, NULL);
				else
					print_error(name, NULL, "command not found");
				exit(127);
			}
			if (errno == EACCES)
			{
				print_errno(name, NULL);
				exit(126);
			}
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		self->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
        self->status = WTERMSIG(status);
	// printf("status: %d\n", status);
	// printf("status: %d\n", self->status);
}
