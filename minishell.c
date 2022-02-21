/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/02/20 20:45:31 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *line;
	size_t size;
	t_stack analysed;

	// ignore some signals?

	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};

		// 1. stdin loop

		// 2. handle Ctrl-\ Ctrl-C Ctrl-D signals like in bash

		// TEST - command + data
		size = 31;
		line = (char *)malloc(size);
		ft_strcpy(line, "echo 'Hello World!' > file.txt");

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
		break ;

		// 4. parse stack of tokens into an abstract syntax tree

		// 5. execute syntax tree

		// 6. free stack of tokens and syntax tree
		if (analysed.token)
			token_destroy(analysed.token);
	}
	return 0;
}
