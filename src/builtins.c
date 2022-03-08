/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:18:59 by msousa            #+#    #+#             */
/*   Updated: 2022/03/08 14:58:47 by msousa           ###   ########.fr       */
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

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);
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
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);

	if (command->argc == 1) {
		// TODO: remove use of getenv
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

	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}

int	builtin_export(t_command *command, t_app *self)
{
	int i;
	char **splitted;
	t_env *new_env;
	t_env *temp;
	char	*found;
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);

	i = 1;
	while(command->argv[i]) {
		temp = self->env;

		splitted = ft_split_single(command->argv[i], '=');
		if (!splitted)
		{
			if (!is_valid_identifier(command->argv[i]))
			{
				ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
				ft_putstr_fd(command->argv[i], STDOUT_FILENO);
				ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
			}
			i++;
			continue ;
		}

		found = get_env(splitted[0], self->env);

		if(!is_valid_identifier(splitted[0]))
		{
			ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
			ft_putstr_fd(splitted[0], STDOUT_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
		}

		if (found)
		{
			while(temp)
			{
				if(ft_streq(temp->key, splitted[0]))
				{
					if(!ft_streq(temp->value, splitted[1]))
					{
						free(temp->value);
						free(found);
						temp->value = ft_strdup(splitted[1]);
					}
					break ;
				}
				temp = temp->next;
			}
		}
		else
		{
			new_env = env_create(command->argv[i]);
			if (!new_env)
				return (1);
			while (temp->next)
				temp = temp->next;
			temp->next = new_env;
		}
		ft_free_string_arrays(splitted);
		i++;
	}

	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}

int	builtin_unset(t_command *command, t_app *self)
{
	int i;
	t_env *temp;
	t_env *previous;
	int stdout_fd;

	stdout_fd = dup(STDOUT_FILENO); // to restore at the end
	run_setup_io(command, self->env);

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

	dup2(stdout_fd, STDOUT_FILENO); // restore stdout
	return (0);
}
