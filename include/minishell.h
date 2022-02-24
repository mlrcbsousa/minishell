/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/02/24 19:12:00 by msousa           ###   ########.fr       */
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

// Functions
void	token_stack_build(char *line, size_t size, t_stack *tokens);
char	**get_binary_paths(char **envp);

#endif
