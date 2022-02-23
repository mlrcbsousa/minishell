/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:39:23 by ngregori          #+#    #+#             */
/*   Updated: 2022/02/23 22:07:34 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Change naming to executables_paths maybe?
char	**get_binary_paths(char **envp)
{
	char **paths;

	paths = NULL;
	// loops over each env variable until it find path, then creates an array
	// with each path to binary files
	while(*envp && ft_strncmp("PATH=", *envp, 5))
		envp++;
	if (*envp)
		paths = ft_split(*envp + 5, ':');
	//need to add "/" to the end of each binary path next so that when we are
	// trying to run the commands in a loop we don't need to add "/" to each command

	return paths;
}
