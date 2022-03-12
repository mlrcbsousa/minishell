/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:39:23 by ngregori          #+#    #+#             */
/*   Updated: 2022/03/09 14:41:34 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_binary_paths(t_env *env)
{
	char	**paths;
	char	**save;
	char	*path;

	paths = NULL;
	path = get_env("PATH", env);
	if (path && *path)
		paths = ft_split(path, ':');
	save = paths;
	while (paths && *paths)
	{
		path = ft_strjoin(*paths, "/");
		free(*paths);
		*paths++ = path;
	}
	return (save);
}

void	find_binary_path(t_command *command, t_env *env)
{
	char	**paths;
	char	*path;

	path = NULL;
	paths = get_binary_paths(env);
	if (!paths)
		return ;
	while (*paths)
	{
		path = ft_strjoin(*paths, *command->argv);
		if (!(access(path, F_OK) == -1))
		{
			free(*command->argv);
			*command->argv = path;
			return ;
		}
		free(path);
		paths++;
	}
}
