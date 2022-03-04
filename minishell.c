/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/04 18:14:13 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test tree contents
void	print_astree(t_astree *node)
{
	if (!node)
		return ;
	printf("\n--Node--\n");
	printf("type: %d\n", node->type);
	printf("data: %s\n", node->data);
	print_astree(node->left);
	print_astree(node->right);
}

int main(int argc, char *argv[], char *env[])
{
	t_app self;
	char *line;
	size_t size;
	t_stack analysed;
	t_astree *astree;

	(void)argc;
	(void)argv;
	self = (t_app){ env, signal(SIGINT, sigint_handler) }; // overide "Ctrl-C"
	signal(SIGQUIT, SIG_IGN); // ignore "Ctrl-\"

	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};

		// 1. get standard input
		line = readline("~$ ");
		if(!line) {
			printf("exit\n");
			exit(0);
		}
		add_history(line);
		size = ft_strlen(line);

		// 2. break up line into tokens
		lexical_analysis(line, size, &analysed);
		free(line);

		// TEST - analysed tokens
		t_token *token = analysed.token;
		while (token)
		{
			printf("type: %d, data: %s\n", token->type, token->data);
			token = token->next;
		}

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

		// 5. execute syntax tree
		execute_tree(astree, &self);

		// 6. free stack of tokens and syntax tree
		astree_delete(astree);
		if (analysed.token) // maybe not needed
			token_destroy(analysed.token);
	}
	return 0;
}
