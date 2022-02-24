/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/02/24 21:29:12 by msousa           ###   ########.fr       */
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

int main(int argc, char *argv[], char**envp)
{
	char *line;
	size_t size;
	t_stack analysed;
	t_astree *syntax_astree;
	// char **binary_paths;

	(void)argc;
	(void)argv;
	(void)envp;

	// binary_paths = get_binary_paths(envp);

	// int i = 0;
	// while(binary_paths[i]) printf("%s\n", binary_paths[i++]);

	// return 0;

	// ignore some signals?

	while (1)
	{
		line = NULL;
		size = 0;
		analysed = (t_stack){NULL, 0};

		// 1. stdin loop

		// 2. handle Ctrl-\ Ctrl-C Ctrl-D signals like in bash

		// TEST command + data
		size = 20;
		line = (char *)malloc(size);
		ft_strcpy(line, "echo 'Hello World!'");

		// 3. build a stack of tokens
		token_stack_build(line, size, &analysed);
		free(line);

		// TEST token list from "echo 'Hello World!' > file.txt"
		t_token *token;
		analysed.size = 3;
		analysed.token = (t_token *)malloc(sizeof(t_token));
		token = analysed.token;
		// 1
		token->data = (char *)malloc(5);
		ft_strcpy(token->data, "echo");
		token->type = -1;
		token->next = (t_token *)malloc(sizeof(t_token));
		token = token->next;
		// 2
		token->data = (char *)malloc(15);
		ft_strcpy(token->data, "'Hello World!'");
		token->type = -1;
		token->next = NULL;
		// token->next = (t_token *)malloc(sizeof(t_token));
		// token = token->next;
		// // 3
		// token->data = (char *)malloc(2);
		// ft_strcpy(token->data, ">");
		// token->type = 62; // ascii for '>'
		// token->next = (t_token *)malloc(sizeof(t_token));
		// token = token->next;
		// // 4
		// token->data = (char *)malloc(9);
		// ft_strcpy(token->data, "file.txt");
		// token->type = -1;
		// token->next = NULL;

		// (t_token) { type: -1, 	data: "echo" 						}
		// (t_token) { type: -1, 	data: "'Hello World!'" 	}
		// (t_token) { type: >, 	data: ">" 							}
		// (t_token) { type: -1, 	data: "file.txt" 				}

		token = analysed.token;
		while (token)
		{
			printf("type: %d, data: %s\n", token->type, token->data);
			token = token->next;
		}

		syntax_astree = NULL;
		// 4. parse stack of tokens into an abstract syntax tree
		if (!analysed.size || parse(&analysed, &syntax_astree))
			// continue ;
			;
		else
		{
			printf("successful parsing\n");
			print_astree(syntax_astree);
		}

		astree_delete(syntax_astree);
		// memory leak on tokens stack

		break ;

		// 5. execute syntax tree

		// 6. free stack of tokens and syntax tree
	}
	return 0;
}
