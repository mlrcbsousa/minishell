/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:18:59 by msousa            #+#    #+#             */
/*   Updated: 2022/03/03 22:07:11 by msousa           ###   ########.fr       */
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

int	builtin_echo(t_command *command, t_app *self)
{
	t_bool	with_n;
	int	i;

	(void)self;
	// handle redirects and pipes
	// TODO
	with_n = ft_streq(command->argv[1], "-n");
	i = 1;
	if (with_n)
		i = 2;
	while (i < command->argc - 1)
		printf("%s ", command->argv[i++]);
	printf("%s", command->argv[i]);
	if (!ft_streq(command->argv[1], "-n"))
		printf("\n");
	return (0);
}

int	builtin_cd(t_command *command, t_app *self)
{
	(void)command;
	(void)self;
	return (0);
}

int	builtin_export(t_command *command, t_app *self)
{
	(void)command;
	(void)self;
	return (0);
}

int	builtin_unset(t_command *command, t_app *self)
{
	(void)command;
	(void)self;
	return (0);
}
