/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:05:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 23:31:32 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_command *command, t_app *self)
{
	t_env	*env;
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self->env);
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	env = self->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	dup2(stdout_fd, STDOUT_FILENO);
	return (0);
}

int	builtin_exit(t_command *command, t_app *self)
{
	int	stdout_fd;
	int	status;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self->env);
	status = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (command->argv[1] && !ft_isnumber(command->argv[1]))
	{
		print_error("exit", command->argv[1], "numeric argument required");
		status = 255;
	}
	else if (command->argc > 2)
	{
		print_error("exit", NULL, "too many arguments");
		dup2(stdout_fd, STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	if (command->argc == 1)
		status = EXIT_SUCCESS;
	else
		status = ft_atoi(command->argv[1]);
	free_memory(self, command);
	exit(status);
	return (status);
}

int	builtin_pwd(t_command *command, t_app *self)
{
	char	dir[1024];
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self->env);
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (1);
	}
	getcwd(dir, 1024);
	printf("%s\n", dir);
	dup2(stdout_fd, STDOUT_FILENO);
	return (0);
}
