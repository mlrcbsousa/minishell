/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:42:47 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 18:12:28 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexical_type(char c)
{
	if (c == LEXICAL_QUOTE
		|| c == LEXICAL_PIPE
		|| c == LEXICAL_QUOTE
		|| c == LEXICAL_DQUOTE
		|| c == LEXICAL_WHITESPACE
		|| c == LEXICAL_GREATER
		|| c == LEXICAL_LESSER
		|| c == LEXICAL_NULL)
		return (c);
	else
		return (LEXICAL_DEFAULT);
}

void	token_init(t_token *token, int size)
{
	token->data = (char *)malloc(size + 1);
	*token->data = 0;
	token->type = LEXICAL_NULL;
	token->next = NULL;
}

void	token_destroy(t_token *token)
{
	if (!token)
		return ;
	free(token->data);
	token_destroy(token->next);
	free(token);
}

int	tokens_length(t_token *token)
{
	int	length;

	length = 0;
	while (token)
	{
		length++;
		token = token->next;
	}
	return (length);
}
