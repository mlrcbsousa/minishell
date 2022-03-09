/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 18:18:05 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: make internal exit free all memory
// TODO: make 'exit' show in same line as prompt
// TEST
// printf("successful parsing\n");
// print_astree(astree);
// printf("========================================= NODES END\n");
int	main(int argc, char *argv[], char *env[])
{
	t_app		self;
	char		*line;
	size_t		size;
	t_stack		analysed;
	t_astree	*astree;

	(void)argc;
	(void)argv;
	g_return = 0;
	self = (t_app){NULL, NULL, signal(SIGINT, sigint_handler), NULL};
	signal(SIGQUIT, SIG_IGN);
	set_env(&self, env);
	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};
		line = readline("~$ ");
		if (!line)
		{
			env_destroy(&self);
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		size = ft_strlen(line);
		lexical_analysis(line, size, &analysed, self.env);
		free(line);
		print_tokens(analysed.token);
		astree = NULL;
		if (!analysed.size || parse(&analysed, &astree))
			continue ;
		self.astree = astree;
		token_destroy(analysed.token);
		execute_tree(astree, &self);
		astree_destroy(astree);
	}
	return (0);
}
