/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/04 20:54:10 by msousa           ###   ########.fr       */
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
      printf("minishell: command not found: %s\n", *command->argv);
			exit(1);
    }
  }
	else if (pid < 0) {
		perror("fork");
		return;
	}

	// wait for process to finish
  while (waitpid(pid, NULL, 0) <= 0);
}
