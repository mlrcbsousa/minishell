/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 13:28:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* else if (WIFSIGNALED(status)) */
static int	set_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status));
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

int	run(t_command *command, t_app *self)
{
	int	stdout_fd;
	int	status;

	g_status.pid = fork();
	if (g_status.pid == 0)
	{
		stdout_fd = dup(STDOUT_FILENO);
		run_setup_io(command, self);
		find_binary_path(command, self->env);
		if (execve(*command->argv, command->argv, get_env_raw(self)) == -1)
		{
			dup2(stdout_fd, STDOUT_FILENO);
			run_exit_error(command->argv[0]);
		}
	}
	else if (g_status.pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	waitpid(g_status.pid, &status, 0);
	g_status.pid = 0;
	return (set_status(status));
}
