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

void init_interactive_mode() {
	char *line;
	size_t size;
	t_stack analysed;
	t_astree *astree;

	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};

		// 1. stdin loop
		line = readline("~$ ");
		if(!line) {
			ft_putchar('\n');
			exit(0);
		}
		add_history(line);
		size = ft_strlen(line);

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

		// 6. free stack of tokens and syntax tree
		astree_delete(astree);
		if (analysed.token) // maybe not needed
			token_destroy(analysed.token);
	}
}

void init_non_interactive_mode(char**argv) {
	// instead of reading from terminal, it uses argv as the line

	(void)argv;
}