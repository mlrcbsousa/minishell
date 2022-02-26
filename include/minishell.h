/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/02/26 16:36:57 by msousa           ###   ########.fr       */
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
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

// Enums
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

enum e_state {
	STATE_DQUOTE,
	STATE_QUOTE,
	STATE_ESCAPESEQ,
	STATE_DEFAULT,
};

// Structs
typedef struct s_app t_app;
typedef struct s_token t_token;
typedef struct s_stack t_stack;
typedef struct s_lexer t_lexer;

struct s_app
{
	char **envp; // random, for now not used
};

struct s_token
{
	char *data;
	int type;
	t_token *next;
};

struct s_stack
{
	t_token *token;
	int size;
};

struct s_lexer
{
	t_token *token;
	int state;
	int size;
	int line_i;
	int data_i;
	char c;
	int type;
};

// Functions //

// token
void token_init(t_token *token, int size);
void token_destroy(t_token *token);
int tokens_length(t_token *token);

// lexer
int	lexical_type(char token);
void	lexical_analysis(char *line, int size, t_stack *tokens);
void	lexer_end_read_token(t_lexer *lexer);
void	lexer_type_quote(t_lexer *lexer);
void	lexer_type_dquote(t_lexer *lexer);
void	lexer_type_default(t_lexer *lexer);
void	lexer_type_operator(t_lexer *lexer);

// env
char	**get_binary_paths(void);


#endif
