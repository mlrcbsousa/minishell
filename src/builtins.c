/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:18:59 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 16:04:19 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bin	*get_builtin(char *cmd_path)
{
	static t_bin_def	builtins[7] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	};
	int					i;

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
	int		i;
	int		stdout_fd;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	with_n = ft_streq(command->argv[1], "-n");
	i = 1;
	if (with_n)
		i = 2;
	while (i < command->argc - 1)
		printf("%s ", command->argv[i++]);
	printf("%s", command->argv[i]);
	if (!with_n)
		printf("\n");
	dup2(stdout_fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	builtin_cd(t_command *command, t_app *self)
{
	int		stdout_fd;
	char	*path;
	int		status;

	status = EXIT_SUCCESS;
	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	if (command->argc == 1)
	{
		path = get_env("HOME", self->env);
		if (!path)
		{
			print_error("cd", NULL, "HOME not set");
			status = EXIT_FAILURE;
		}
	}
	else
		path = command->argv[1];
	if (status == EXIT_SUCCESS && chdir(path) == -1)
	{
		print_errno("cd", path);
		status = EXIT_FAILURE;
	}
	dup2(stdout_fd, STDOUT_FILENO);
	return (status);
}

int	builtin_exit(t_command *command, t_app *self)
{
	int	stdout_fd;
	int	status;

	stdout_fd = dup(STDOUT_FILENO);
	run_setup_io(command, self);
	status = EXIT_SUCCESS;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (command->argv[1] && !ft_isnumber(command->argv[1]))
	{
		print_error("exit", command->argv[1], "numeric argument required");
		status = 255;
	}
	else if (command->argc > 2)
	{
		dup2(stdout_fd, STDOUT_FILENO);
		print_error("exit", NULL, "too many arguments");
		return (EXIT_FAILURE);
	}
	if (command->argc != 1)
		status = ft_atoi(command->argv[1]);
	free_memory(self, command);
	dup2(stdout_fd, STDOUT_FILENO);
	exit(status);
	return (status);
}
