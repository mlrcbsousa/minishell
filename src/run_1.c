/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:37:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 17:39:51 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_setup_redirect_in(t_command *command)
{
	int fd;

	if (command->redirect_in)
	{
		fd = open(command->redirect_in, O_RDONLY);
		if (fd == -1)
		{
			perror(command->redirect_in);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
	}
}

void	run_setup_redirect_out(t_command *command)
{
	int fd;

	if (command->redirect_out)
	{
		// https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
		fd = open(command->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
									S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1)
		{
			perror(command->redirect_out);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
	}
}

// redirect stdin or stdout to file
void	run_setup_redirects(t_command *command)
{
	run_setup_redirect_in(command);
	run_setup_redirect_out(command);
}
