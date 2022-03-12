/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:21:53 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 14:22:13 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print_command(&command);
void	execute_simple_command(t_astree *simple_command_node,
	t_executor executor, t_app *self)
{
	t_command	command;

	command = (t_command){0, NULL, FALSE, FALSE, 0, 0, 0, 0};
	command_init(simple_command_node, &command, executor);
	command_execute(&command, self);
	command_destroy(&command);
}
