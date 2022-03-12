/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:05:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 16:13:07 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_command *command, t_app *self)
{
	t_env	*env;
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (EXIT_FAILURE);
	}
	env = self->env;
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	dup2(stdout_fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	builtin_pwd(t_command *command, t_app *self)
{
	char	dir[1024];
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	if (command->argc != 1)
	{
		printf("Wrong number of arguments!\n");
		return (EXIT_FAILURE);
	}
	getcwd(dir, 1024);
	printf("%s\n", dir);
	dup2(stdout_fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

static void	unset_env(t_env *env, t_env *previous, t_app *self)
{
	free(env->key);
	free(env->value);
	if (env == previous)
		self->env = env->next;
	else
		previous->next = env->next;
	free(env);
}

int	builtin_unset(t_command *command, t_app *self)
{
	int		i;
	t_env	*temp;
	t_env	*previous;
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	i = 0;
	while (command->argv[++i])
	{
		temp = self->env;
		previous = self->env;
		while (temp)
		{
			if (ft_streq(temp->key, command->argv[i]))
			{
				unset_env(temp, previous, self);
				break ;
			}
			previous = temp;
			temp = temp->next;
		}
	}
	dup2(stdout_fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
