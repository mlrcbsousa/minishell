/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:18:59 by msousa            #+#    #+#             */
/*   Updated: 2022/03/01 21:05:39 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*get_builtin(char *cmd_path)
{
	// built-ins
	// ◦ echo with option -n
	// ◦ cd with only a relative or absolute path ◦ pwd with no options
	// ◦ export with no options
	// ◦ unset with no options
	// ◦ env with no options or arguments
	// ◦ exit with no options
	static t_builtin_def	builtins[6] = {
		{"echo", builtin_echo},
		{"cd", builtin_cd},
		{"export", builtin_export},
		{"unset", builtin_unset},
		{"env", builtin_env},
		{"exit", builtin_exit},
	};
	int i;

	i = 0;
	while (i < 6)
	{
		if (ft_streq(cmd_path, builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
}

void	builtin_echo(t_command *command)
{
	t_bool	with_n;

	if (command->argc > 3)
	{
		printf("echo: Too many arguments\n");
		return ;
	}

	if (command->argc == 1)
	{
		printf("\n");
		return ;
	}

	with_n = ft_streq(command->argv[1], "-n");

	if (command->argc == 2)
	{
		if (with_n)
			printf("");
		else
			printf("%s\n", command->argv[1]);
		return ;
	}
	// argc == 3
	if (with_n)
		printf("%s", command->argv[2]);
	else
		printf("echo: Invalid option\n");
}

void	builtin_cd(t_command *command)
{
	(void)command;
}

void	builtin_export(t_command *command)
{
	(void)command;
}

void	builtin_unset(t_command *command)
{
	(void)command;
}
