/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/02/19 18:44:24 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef DEBUG_MODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)
# endif

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

#endif
