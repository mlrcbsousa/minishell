/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:42:41 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 15:34:56 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_invalid_identifier(char *identifier)
{
	if (is_valid_identifier(identifier))
		return ;
	ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
	ft_putstr_fd(identifier, STDOUT_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
}

static void	export_env_update(char *found, t_env *env, char *splitted[])
{
	{
		while (env)
		{
			if (ft_streq(env->key, splitted[0]))
			{
				if (!ft_streq(env->value, splitted[1]))
				{
					free(env->value);
					free(found);
					env->value = ft_strdup(splitted[1]);
				}
				break ;
			}
			env = env->next;
		}
	}
}

static int	export_env_create(char *env_raw, t_env *env)
{
	t_env	*new_env;

	new_env = env_create(env_raw);
	if (!new_env)
		return (EXIT_FAILURE);
	while (env->next)
		env = env->next;
	env->next = new_env;
	return (EXIT_SUCCESS);
}

static int	export_env_add_or_update(t_env *env, char *splitted[], char *cmd)
{
	char	*found;
	int		status;

	check_invalid_identifier(splitted[0]);
	status = EXIT_SUCCESS;
	found = get_env(splitted[0], env);
	if (found)
		export_env_update(found, env, splitted);
	else
	{
		status = export_env_create(cmd, env);
		if (status == EXIT_FAILURE)
			ft_free_string_arrays(splitted);
	}
	return (status);
}

int	builtin_export(t_command *command, t_app *self)
{
	int		i;
	int		status;
	char	**splitted;
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	i = 0;
	status = EXIT_SUCCESS;
	while (command->argv[++i])
	{
		splitted = ft_split_first(command->argv[i], '=');
		if (!splitted)
		{
			check_invalid_identifier(command->argv[i++]);
			continue ;
		}
		status = export_env_add_or_update(self->env, splitted,
				command->argv[i]);
		if (status == EXIT_FAILURE)
			break ;
		ft_free_string_arrays(splitted);
	}
	dup2(stdout_fd, STDOUT_FILENO);
	return (status);
}
