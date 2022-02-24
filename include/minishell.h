/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/02/24 22:55:28 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef DEBUG_MODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)
# endif

# include <stdio.h>

# include "libft.h"

// Enums
typedef enum e_node {
	NODE_PIPE = 1, // have to start at one to not override in astree_set_data()
	NODE_SEQ,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_DATA,
} t_node;

enum e_lexical {
	LEXICAL_DEFAULT = -1,
	LEXICAL_PIPE = '|',
	LEXICAL_QUOTE = '\'',
	LEXICAL_DQUOTE = '\"',
	LEXICAL_WHITESPACE = ' ',
	LEXICAL_ESCAPESEQUENCE = '\\',
	LEXICAL_GREATER = '>',
	// LEXICAL_GGREATER = '>>',
	LEXICAL_LESSER = '<',
	// LEXICAL_LLESSER = '<<',
	LEXICAL_NULL = 0,
};

// Structs
typedef struct s_app t_app;

struct s_app
{
	int	something;
};

typedef struct s_token t_token;
typedef struct s_stack t_stack;
typedef struct s_astree t_astree;
typedef struct s_parser t_parser;

struct s_token
{
	int type;
	char *data;
	t_token *next;
};
struct s_stack
{
	t_token *token;
	int size;
};

struct s_astree
{
	int type;
	char *data;
	t_astree *left;
	t_astree *right;
};

struct s_parser
{
	t_token	*current_token;
};

// Functions
void	token_stack_build(char *line, size_t size, t_stack *tokens);
int parse(t_stack *analysed, t_astree **syntax_astree);

// Abstract Syntax Tree
void astree_add_branches(t_astree *root , t_astree *left , t_astree *right);
void astree_set_type(t_astree *node , t_node type);
void astree_set_data(t_astree *node , char *data);
void astree_delete(t_astree *node);
char	**get_binary_paths(char **envp);

// Bakus Naur Parser
t_bool	match(int token_type, char **buffer, t_parser *parser);
t_astree* command_line(t_parser *parser);
t_astree* command_line_a(t_parser *parser);
t_astree* command(t_parser *parser);
t_astree* command_a(t_parser *parser);
t_astree* command_b(t_parser *parser);
t_astree* simple_command(t_parser *parser);
t_astree* token_list(t_parser *parser);
t_astree	*token_list_a(t_parser *parser);

#endif
