/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:18:59 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 15:26:46 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*get_builtin(char *cmd_path)
{
	static t_builtin_def	builtins[7] = {
		{"echo", builtin_echo},
		{"cd", builtin_cd},
		{"pwd", builtin_pwd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit},
	};
	int i;

	i = 0;
	while (i < 7)
	{
		if (ft_streq(cmd_path, builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}

int	builtin_echo(t_command *command, t_app *self)
{
	t_bool	with_n;
	int	i;
	int stdout_fd;

	(void)self;
	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_redirect_out(command);
	run_setup_pipe_write(command);
	with_n = ft_streq(command->argv[1], "-n");
	i = 1;
	if (with_n)
		i = 2;
	while (i < command->argc - 1)
		printf("%s ", command->argv[i++]);
	printf("%s", command->argv[i]);
	if (!ft_streq(command->argv[1], "-n"))
		printf("\n");
	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}

int	builtin_cd(t_command *command, t_app *self)
{
	(void)self;

	if (command->argc == 1) {
		char *home = getenv("HOME");

		if(home)
		{
			if(chdir(home) == -1) {
				ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
				ft_putstr_fd(home, STDERR_FILENO);
				ft_putstr_fd(": ", STDERR_FILENO);
				perror("");
				return (1);
			}
			return (0);
		}

		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return 1;
	}

	if(chdir(command->argv[1]) == -1) {
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(command->argv[1], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror("");
	}

	return (0);
}

int	builtin_export(t_command *command, t_app *self)
{
	int i;
	char **splitted;
	t_env *new_env;
	t_env *temp;
	int	found;

	i = 1;
	while(command->argv[i]) {
		temp = self->env;
		
		splitted = ft_split_single(command->argv[i], '=');
		if(!splitted[1])
		{
			ft_free_string_arrays(splitted);
			continue;
		}

		found = 0;

		while(temp) {
			if(ft_streq(temp->key, splitted[0]))
			{
				found = 1;
				if(!ft_streq(temp->value, splitted[1]))
				{
					free(temp->value);
					temp->value = ft_strdup(splitted[1]);
				}
				break;
			}
			temp = temp->next;
		}

		if(!found) {
			new_env = malloc(sizeof(t_env));
			if(!new_env)
				return (1);

			new_env->key = ft_strdup(splitted[0]);

			new_env->value = ft_strdup(splitted[1]);

			new_env->next = NULL;

			temp = self->env;
			while(temp->next)
				temp = temp->next;
			temp->next = new_env;
		}
		ft_free_string_arrays(splitted);
		i++;
	}
	
	return (0);
}

int	builtin_unset(t_command *command, t_app *self)
{
	int i;
	t_env *temp;
	t_env *previous;

	i = 1;
	while(command->argv[i]) {
		temp = self->env;
		previous = self->env;
		
		while(temp) {
			if(strcmp(temp->key, command->argv[i]) == 0) {
				free(temp->key);
				temp->key = NULL;

				free(temp->value);
				temp->value=NULL;

				if(temp == previous) {
					self->env = temp->next;
				}
				else
					previous->next = temp->next;
				free(temp);
				break;
			}
			previous = temp;
			temp = temp->next;
		}
		i++;
	}

	return (0);
}
