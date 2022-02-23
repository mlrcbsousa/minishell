/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:39:23 by ngregori          #+#    #+#             */
/*   Updated: 2022/02/22 22:02:50 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Change naming to executables_paths maybe?
char	**get_binary_paths(char **envp) {
	int i = -1;
	char **paths;

	paths = NULL;
	while(envp[++i]) // loops over each env variable until it find path, then creates an array with each path to binary files
	{
		if(ft_strncmp("PATH=", envp[i], 5) == 0)
		{
			paths = ft_split(&envp[i][5], ':');

			//need to add "/" to the end of each binary path next so that when we are trying to run the commands in a loop we don't need to add "/" to each command
		}
	}
	
	return paths;
}
