/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/02/25 22:34:45 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void) // no need for arguments can use `getenv("PATH")`
{
	char *line;
	size_t size;
	t_stack analysed;

	// ignore "Ctrl-C"
	signal(SIGINT, SIG_IGN);
	// ignore "Ctrl-\"
  signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};

		// 1. stdin loop
		line = readline("~$ ");
		size = ft_strlen(line);

		// 2. handle Ctrl-D
		// aparently no signal for this

		// 3. break up line into tokens
		lexical_analysis(line, size, &analysed);
		free(line);

		// TEST - analysed tokens
		t_token *token = analysed.token;
		while (token)
		{
			printf("type: %d, data: %s\n", token->type, token->data);
			token = token->next;
		}

		// 4. parse stack of tokens into an abstract syntax tree

		// 5. execute syntax tree

		// 6. free stack of tokens and syntax tree
		if (analysed.token)
			token_destroy(analysed.token);
	}
	return 0;
}
