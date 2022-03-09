/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 17:44:54 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_setup_io_in(t_io *io, t_env *env)
{
	while (io)
	{
		if (io->type == NODE_REDIRECT_IN)
			run_setup_redirect_in(io);
		if (io->type == NODE_HEREDOC)
			run_setup_heredoc(io, env);
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

void	run_setup_io(t_command *command, t_env *env)
{
	// redirect stdin from file if specified
	if(command->redirect_in)
		run_setup_io_in(command->redirect_in, env);

  // redirect stdout to file if specified
	if(command->redirect_out)
		run_setup_io_out(command->redirect_out);

	// read from stdin pipe
	if (command->stdin_pipe)
		dup2(command->pipe_read, STDIN_FILENO);

	// write to stdout pipe
	if (command->stdout_pipe)
		dup2(command->pipe_write, STDOUT_FILENO);
}

void	run(t_command *command, t_app *self)
{
	pid_t pid;
	int stdout_fd;

	pid = fork();
  if(pid == 0)
	{
		// restore sigint in the child process
		signal(SIGINT, self->sigint_handler);

		// handle pipes and redirects
		stdout_fd = dup(STDOUT_FILENO); // to restore at the end
		run_setup_io(command, self->env);

		// check if file is in bin path
		find_binary_path(command, self->env);
		printf("%s\n", *command->argv);

		if (execve(*command->argv, command->argv, get_env_raw(self)) == -1)
		{
			dup2(stdout_fd, STDOUT_FILENO); // restore stdout
      printf("%s: command not found\n", *command->argv);
			exit(127);
		}
	}
	else if (pid < 0) {
		perror("fork");
		return;
	}

	// wait for process to finish
  waitpid(pid, NULL, 0);
}
