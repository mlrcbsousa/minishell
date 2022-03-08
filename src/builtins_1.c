/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:05:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/08 15:01:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_command *command, t_app *self)
{
	t_env *env;
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);

	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	env = self->env;
	while(env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}

int	builtin_exit(t_command *command, t_app *self)
{
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);

	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	command_destroy(command);
	astree_destroy(self->astree);
	env_destroy(self);
	printf("exit\n");
	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	exit(0);
	return (0);
}

int	builtin_pwd(t_command *command, t_app *self)
{
	char dir[1024];
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	getcwd(dir, 1024);
	printf("%s\n", dir);
	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}
