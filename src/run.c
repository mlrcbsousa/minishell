/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 12:01:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_setup_pipe_write(t_command *command)
{
	// write to stdout pipe
	if (command->stdout_pipe)
		dup2(command->pipe_write, STDOUT_FILENO);
}

void	run_setup_io_out(t_command *command)
{
	run_setup_redirect_out(command);
	run_setup_append(command);
	run_setup_pipe_write(command);
}

void	run_setup_io_in(t_command *command)
{
	run_setup_redirect_in(command);
	run_setup_heredoc(command);
	run_setup_pipe_read(command);
}

void	run_setup_io(t_command *command)
{
	run_setup_io_in(command);
	run_setup_io_out(command);
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
		run_setup_io(command);

		// check if file is in bin path
		find_binary_path(command);
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
