/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/02/22 20:11:56 by msousa           ###   ########.fr       */
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

// Structs
typedef struct s_app t_app;

struct s_app
{
	int	something;
};

typedef struct s_token t_token;
typedef struct s_stack t_stack;
typedef struct s_btree t_btree;

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

struct s_btree
{
	int type;
	char *data;
	t_btree *left;
	t_btree *right;
};

// Functions
void	token_stack_build(char *line, size_t size, t_stack *tokens);
int parse(t_stack *analysed, t_btree **syntax_tree);

#endif
