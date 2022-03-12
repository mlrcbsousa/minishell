/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 04:19:11 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_status(int status)
{
	// if (g_status.value == 130)
	// 	return ;
	printf("DEBUG: status: %d\n", status);
	printf("DEBUG: WIFEXITED(status): %d\n", WIFEXITED(status));
	printf("DEBUG: WEXITSTATUS(status): %d\n", WEXITSTATUS(status));
	printf("DEBUG: WIFSIGNALED(status): %d\n", WIFSIGNALED(status));
	printf("DEBUG: WTERMSIG(status): %d\n", WTERMSIG(status));
	if (WIFEXITED(status))
		g_status.value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_status.value = WTERMSIG(status);
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
	int		stdout_fd;
	int		status;

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
		g_status.value = EXIT_FAILURE;
		return ;
	}
	waitpid(g_status.pid, &status, 0);
	g_status.pid = 0;
	set_status(status);
}
