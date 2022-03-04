/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/04 21:49:47 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run(t_command *command, t_app *self)
{
	pid_t pid;

	pid = fork();

  	if(pid == 0)
	{
		// restore sigint in the child process
		signal(SIGINT, self->sigint_handler);

		// handle pipes and redirects
		// TODO

		// maybe this should be somewhere else, like the command init function
		// check if file is in bin path
		find_binary_path(command);
		printf("%s\n", *command->argv);
		if (execve(*command->argv, command->argv, self->env) == -1)
		{
      		printf("%s: command not found\n", *command->argv);
			exit(127);
    	}
  	}
	else if (pid < 0) {
		perror("fork");
		return;
	}

	// wait for process to finish
  waitpid(pid, NULL, 0);
}
