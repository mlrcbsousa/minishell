/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 01:57:19 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 13:31:11 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	script_read(int fd, t_app *self)
{
	int		status;
	char	*line;

	status = 1;
	line = NULL;
	while (status > 0)
	{
		status = get_next_line(fd, &line);
		app_loop(self, line);
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (g_status.value);
}

int	script_open(char *filename, t_app *self)
{
	int	fd;
	int	status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_errno(filename, NULL);
		return (EXIT_FAILURE);
	}
	status = script_read(fd, self);
	if (close(fd))
	{
		print_errno(filename, NULL);
		return (EXIT_FAILURE);
	}
	if (status < 0)
		return (EXIT_FAILURE);
	return (status);
}
