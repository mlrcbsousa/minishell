/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:05:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 18:40:13 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_command *command, t_app *self)
{
	int stdout_fd;
	char **env;

	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_redirect_out(command);
	run_setup_pipe_write(command);
	env = self->env;
	while(env && *env)
		printf("%s\n", *env++);
	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}

int	builtin_exit(t_command *command, t_app *self)
{
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	command_destroy(command);
	astree_destroy(self->astree);
	printf("exit\n");
	exit(0);
	return (0);
}

int	builtin_pwd(t_command *command, t_app *self)
{
	int stdout_fd;
	char dir[1024];

	(void)self;
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_redirect_out(command);
	run_setup_pipe_write(command);
	getcwd(dir, 1024);
	printf("%s\n", dir);
	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}
