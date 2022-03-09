/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:05:36 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 18:06:49 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: check what returns from split "key="
// TODO: check value might be empty
t_env	*env_create(char *raw)
{
	char	**data;
	t_env	*env;

	data = ft_split_first(raw, '=');
	env = (t_env *)malloc(sizeof(t_env));
	env->key = *data++;
	env->value = *data;
	env->next = NULL;
	return (env);
}

void	env_destroy(t_app *self)
{
	t_env	*env;

	if (self->env_raw)
	{
		while (*self->env_raw)
			free(*self->env_raw++);
		free(self->env_raw);
	}
	while (self->env)
	{
		env = self->env;
		self->env = self->env->next;
		free(env->key);
		free(env->value);
		free(env);
	}
}

static int	env_length(t_env *env)
{
	int	length;

	length = 0;
	while (env)
	{
		length++;
		env = env->next;
	}
	return (length);
}

char	**get_env_raw(t_app *self)
{
	t_env	*env;
	char	*save;
	int		i;

	i = 0;
	env = self->env;
	self->env_raw = (char **)malloc(sizeof(char *) * (env_length(env) + 1));
	while (env)
	{
		save = ft_strjoin(env->key, "=");
		self->env_raw[i] = ft_strjoin(save, env->value);
		free(save);
		i++;
		env = env->next;
	}
	self->env_raw[i] = NULL;
	return (self->env_raw);
}

void	set_env(t_app *self, char **raw)
{
	t_env	*env;

	if (!raw || !*raw)
		return ;
	self->env = env_create(*raw++);
	env = self->env;
	while (raw && *raw)
	{
		env->next = env_create(*raw++);
		env = env->next;
	}
}
