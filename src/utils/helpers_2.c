/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:15:45 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 16:16:00 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(t_app *self, t_command *command)
{
	if (command)
		command_destroy(command);
	if (self)
	{
		if (self->astree)
			astree_destroy(self->astree);
		env_destroy(self);
	}
}
