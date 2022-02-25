/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/02/25 21:33:32 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void) // no need for arguments can use `getenv("PATH")`
{
	char *line;
	size_t size;
	t_stack tokens;

	// ignore "Ctrl-C"
	// will need to save this to untoggle on child
	// will need to use something else other then signal ignore
	signal(SIGINT, SIG_IGN);
	// ignore "Ctrl-\"
  signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		line = NULL;
		size = 0;
		tokens = (t_stack){NULL, 0};

		// 1. stdin loop
		line = readline("~$ ");
		size = ft_strlen(line);

		printf("%s\n", line);

		// 2. handle Ctrl-D
		// aparently no signal for this

		// 3. build a stack of tokens
		token_stack_build(line, size, &tokens);
		free(line);

		// 4. parse stack of tokens into an abstract syntax tree

		// 5. execute syntax tree

		// 6. free stack of tokens and syntax tree
	}
	return 0;
}
