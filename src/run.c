/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 15:56:36 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirect stdin or stdout to file
void	run_setup_redirects(t_command *command)
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
	else if (command->redirect_out)
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

void	run_setup_pipes(t_command *command)
{
	// read from stdin piepe
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
		run_setup_redirects(command);
		run_setup_pipes(command);

		// maybe this should be somewhere else, like the command init function
		// check if file is in bin path
		find_binary_path(command);
		printf("%s\n", *command->argv);
		if (execve(*command->argv, command->argv, self->env) == -1)
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
