/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/06 11:33:53 by msousa           ###   ########.fr       */
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

// Test tokens contents
void	print_tokens(t_token *token)
{
	if (!token)
		return ;
	while (token)
	{
		printf("\n--Token--\n");
		printf("type: %d\n", token->type);
		printf("data: %s\n", token->data);
		token = token->next;
	}
}

void	test() {
	char **cmds = ft_split("cd", ' ');
	t_command test = {0, cmds, 0, 0, 0, 0, 0, 0};

	builtin_cd(&test, NULL);
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

	// overide "Ctrl-C"
	self = (t_app){ NULL, NULL, signal(SIGINT, sigint_handler), NULL };
	// ignore "Ctrl-\"
	signal(SIGQUIT, SIG_IGN);

	// transform env into linked list
	set_env(&self, env);

	// test();

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
		self.astree = astree;
		token_destroy(analysed.token);

		// 5. execute syntax tree
		execute_tree(astree, &self);

		// 6. free memory
		astree_destroy(astree);
	}
	return 0;
}
