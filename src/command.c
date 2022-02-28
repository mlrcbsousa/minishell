/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 18:56:15 by msousa            #+#    #+#             */
/*   Updated: 2022/02/28 20:03:36 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_command *command)
{
	(void)command;
}

void init_command(t_astree *node,
									t_command *command,
									t_executor executor)
{
	(void)node;
	(void)command;
	(void)executor;
}

void destroy_command(t_command *command)
{
	(void)command;
}
