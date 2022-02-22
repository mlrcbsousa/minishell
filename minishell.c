/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngregori <ngregori@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/02/22 21:25:19 by ngregori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char**envp)
{
	char *line;
	size_t size;
	t_stack tokens;

	// ignore some signals?

	while (1)
	{
		line = NULL;
		size = 0;
		tokens = (t_stack){NULL, 0};

		// 1. stdin loop

		// 2. handle Ctrl-\ Ctrl-C Ctrl-D signals like in bash

		// TEST command + data
		size = 20;
		line = (char *)malloc(size);
		ft_strcpy(line, "echo 'Hello World!'");

		// 3. build a stack of tokens
		token_stack_build(line, size, &tokens);
		free(line);

		// 4. parse stack of tokens into an abstract syntax tree

		// 5. execute syntax tree

		// 6. free stack of tokens and syntax tree
	}
	return 0;
}
