/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:39:23 by ngregori          #+#    #+#             */
/*   Updated: 2022/02/25 21:07:22 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Change naming to executables_paths maybe?
char	**get_binary_paths(void)
{
	char **paths;
	char *envp;

	paths = NULL;
	envp = getenv("PATH");
	if (*envp)
		paths = ft_split(envp, ':');

	//need to add "/" to the end of each binary path next so that when we are
	// trying to run the commands in a loop we don't need to add "/" to each command

	return paths;
}
