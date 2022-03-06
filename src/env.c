/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 18:05:36 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 15:19:25 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env *env_create(char *raw)
{
	char **data;
	t_env *env;

	// TODO: split only on first '='
	data = ft_split(raw, '=');
	env = (t_env *)malloc(sizeof(t_env));

	// key
	env->key = (char *)malloc(ft_strlen(*data) + 1);
	env->key = ft_strcpy(env->key, *(data));

	// value
	env->value = (char *)malloc(ft_strlen(*(data + 1)) + 1);
	env->value = ft_strcpy(env->value, *(data + 1));

	// value might be empty

	env->next = NULL;

	// TODO: free each string inside
	free(data);
	return (env);
}

void env_destroy(t_app *self)
{
	t_env *env;

	if (self->env_raw)
	{
		while(*self->env_raw)
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
	char	*save;
	int i = 0;

	self->env_raw = (char **)malloc(sizeof(char *) * (env_length(self->env) + 1));
	env = self->env;
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

// transform env into linked list and set head on self
void	set_env(t_app *self, char **raw)
{
	t_env *env;

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
