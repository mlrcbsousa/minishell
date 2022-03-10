/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 02:38:35 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_status(t_app *self, int status)
{
	if (WIFEXITED(status))
		self->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		self->status = WTERMSIG(status);
}

static void	run_exit_error(char *name)
{
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

void	run(t_command *command, t_app *self)
{
	pid_t	pid;
	int		stdout_fd;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, self->sigint_handler);
		stdout_fd = dup(STDOUT_FILENO);
		run_setup_io(command, self);
		find_binary_path(command, self->env);
		if (execve(*command->argv, command->argv, get_env_raw(self)) == -1)
		{
			dup2(stdout_fd, STDOUT_FILENO);
			run_exit_error(command->argv[0]);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	waitpid(pid, &status, 0);
	set_status(self, status);
}
