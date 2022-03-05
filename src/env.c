/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:05:36 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 18:16:32 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(t_app *self)
{
	t_env	*env;
	int	i;

	i = 0;
	env = self->env;
	while (env)
	{
		i++;
		env = env->next;
	}
	// malloc o char** baseado em i
	// join env.key com env.value  e =
}

void	set_env(t_app *self, char **env)
{
	// transform env into linked list and set head on self
}
