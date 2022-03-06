/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:05:36 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 12:29:53 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env *env_create(char *raw)
{
	char **data;
	t_env *env;

	// split only on first '='
	data = ft_split(raw, '=');
	env = (t_env *)malloc(sizeof(t_env));

	// key
	env->key = (char *)malloc(ft_strlen(*data) + 1);
	env->key = ft_strcpy(env->key, *(data + 1));

	// value
	env->value = (char *)malloc(ft_strlen(*data) + 1);
	env->value = ft_strcpy(env->value, *data);

	// value might be empty

	env->next = NULL;

	// free each string inside
	free(data);
	return (env);
}

// add self as arg and remove also raw if present
void env_destroy(t_env *env)
{
	if (!env)
		return;
	free(env->key);
	free(env->value);
	env_destroy(env->next);
	free(env);
}

static int env_length(t_env *env)
{
	int length;

	length = 0;
	while (env)
	{
		length++;
		env = env->next;
	}
	return (length);
}

char	**get_env(t_app *self)
{
	t_env	*env;
	char	**raw;
	char	*save;

	self->env_raw = (char **)malloc(env_length(self->env) + 1);
	env = self->env;
	raw = self->env_raw;
	while (env)
	{
		save = ft_strjoin(env->key, "=");
		*raw = ft_strjoin(save, env->value);
		free(save);
		raw++;
		env = env->next;
	}
	*raw = NULL;
	return (self->env_raw);
}

// transform env into linked list and set head on self
void	set_env(t_app *self, char **raw)
{
	t_env *env;

	if (!raw || !*raw)
		return ;

	self->env = env_create(*raw++);
	env = self->env->next;
	while (raw && *raw)
	{
		env = env_create(*raw++);
		env = env->next;
	}
}
