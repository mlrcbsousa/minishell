/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 20:41:51 by msousa            #+#    #+#             */
/*   Updated: 2022/03/03 22:06:01 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// is this allowed because I get error with __environ
extern char **environ;

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

		// is it better to use global or envp from args since we will need to
		// set and unset
		if (execve(*command->argv, command->argv, environ) == -1)
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
