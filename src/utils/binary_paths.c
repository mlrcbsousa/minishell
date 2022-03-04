/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:39:23 by ngregori          #+#    #+#             */
/*   Updated: 2022/03/04 20:52:59 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Change naming to executables_paths maybe?
char	**get_binary_paths(void)
{
	char **paths;
	char **save;
	char *path;

	paths = NULL;
	path = getenv("PATH");
	if (*path)
		paths = ft_split(path, ':');
	save = paths;
	while (*paths)
	{
		path = ft_strjoin(*paths, "/");
		free(*paths);
		*paths++ = path;
	}
	return save;
}

void	find_binary_path(t_command *command)
{
	char **paths;
	char *path;

	path = NULL;
	paths = get_binary_paths();
	if (!paths)
		return ;
	while (*paths)
	{
		path = ft_strjoin(*paths, *command->argv);
		if (!(access(path, F_OK) == -1))
		{
			// file exists
			free(*command->argv);
			*command->argv = path;
		}
		free(path);
		paths++;
	}
}
