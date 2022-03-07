/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:43:28 by msousa            #+#    #+#             */
/*   Updated: 2022/03/07 12:12:51 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_expanded_val(char **str, t_app *self) {
	t_env *temp;

	if(!str || !str[0][1] || str[0][0] != '$')
		return(*str);

	temp = self->env;
	while(temp) {
		if(ft_streq(temp->key, &str[0][1])) {

			free(*str);
			return (ft_strdup(temp->value));
		}

		temp = temp->next;
	}
	return (NULL);
}

char	*get_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_streq(env->key, key))
		{
			// key doesnt have value
			// TODO: return empty string (which should be env->value)
			if (!ft_strlen(env->value))
				printf("empty string\n");
			return (env->value);
		}
		env = env->next;
	}
	// key doesnt exist
	return (NULL);
}

char	*get_expanded(char *raw, t_env *env)
{
	char *expanded;

	(void)env;

	expanded = NULL;
	// only if double quotes or no quotes
	if (!should_expand(raw))
		return (ft_strdup(raw));


	while(*raw != '$')
	{

		raw++;
	}
	// if ?


	// else
	expanded = (char *)malloc(ft_strlen(raw) + 1);
	ft_strcpy(expanded, raw);
	return (expanded);
}
