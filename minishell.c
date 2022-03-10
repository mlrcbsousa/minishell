/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 03:28:43 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO: make internal exit free all memory
** TODO: make 'exit' show in same line as prompt
** TEST
		print_tokens(analysed.token);

** printf("successful parsing\n");
** print_astree(astree);
** printf("========================================= NODES END\n"); */
int	main(int argc, char *argv[], char *env[])
{
	t_app		self;
	char		*line;
	size_t		size;
	t_stack		analysed;
	t_astree	*astree;

	(void)argc;
	(void)argv;
	self = (t_app){NULL, NULL, 0, NULL, 0};
	self.sigint_handler = signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
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
		lexical_analysis(line, size, &analysed, &self);
		free(line);
		astree = NULL;
		self.status = parse(&analysed, &astree);
		if (!analysed.size || self.status)
			continue ;
		self.astree = astree;
		token_destroy(analysed.token);
		execute_tree(astree, &self);
		astree_destroy(astree);
	}
	return (0);
}
