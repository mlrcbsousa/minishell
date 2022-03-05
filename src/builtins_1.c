/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:05:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 17:16:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_command *command, t_app *self)
{
	(void)command;
	(void)self;
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
	token_destroy(self->tokens);
	printf("exit\n");
	exit(0);
	return (0);
}
