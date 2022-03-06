/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 21:06:12 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_app self;
	char *line;
	size_t size;
	t_stack analysed;
	t_astree *astree;

	(void)argc;
	(void)argv;

	// overide "Ctrl-C"
	self = (t_app){ NULL, NULL, signal(SIGINT, sigint_handler), NULL };

	// ignore "Ctrl-\"
	signal(SIGQUIT, SIG_IGN);

	set_env(&self, env);

	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};

		// 1. get standard input
		line = readline("~$ ");
		if(!line) {
			// TODO: make internal exit free all memory
			// TODO: make 'exit' show in same line as prompt
			env_destroy(&self);
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		size = ft_strlen(line);

		// 2. break up line into tokens
		lexical_analysis(line, size, &analysed);
		free(line);

		// TEST - analysed tokens
		print_tokens(analysed.token);

		// 3. parse stack of tokens into an abstract syntax tree
		astree = NULL;
		if (!analysed.size || parse(&analysed, &astree))
			// continue ;
			;
		else
		{
			printf("successful parsing\n");
			print_astree(astree);
		}
		// TODO: check if needed
		self.astree = astree;
		token_destroy(analysed.token);

		// 5. execute syntax tree
		execute_tree(astree, &self);

		// 6. free memory
		astree_destroy(astree);
	}
	return 0;
}
