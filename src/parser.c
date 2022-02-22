/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:37:24 by msousa            #+#    #+#             */
/*   Updated: 2022/02/22 20:57:02 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_astree* command_line();			//	test all command line composition in order
t_astree* command_line_a();		//	<job> ';' <command line>
t_astree* command_line_b();		//	<job> ';'
t_astree* command_line_c();		//	<job>

t_astree* job();							// test all job composition in order
t_astree* job_a();						// <command> '|' <job>
t_astree* job_b();						// <command>

t_astree* command();					// test all command composition in order
t_astree* command_a();				//	<simple command> '<' <filename>
t_astree* command_b();				//	<simple command> '>' <filename>
t_astree* command_c();				//	<simple command>

t_astree* simple_command();		// test simple command composition
t_astree* simple_command_a();	// <pathname> <token list>

t_astree* token_list();				// test tokenlist composition
t_astree* token_list_a();			// <token> <token list>
t_astree* token_list_b();			// EMPTY

typedef struct s_parser
{
	t_token	*token;
} t_parser;

int parse(t_stack *analysed, t_astree **syntax_astree)
{
	t_parser	parser;

	(void)syntax_astree;
	if (!analysed->size)
		return (-1);

	parser.token = analysed->token;
	// *syntax_astree = command_line();

	// If command filter didn't reach the end of the token list
	if (parser.token && parser.token->type)
	{
		printf("Syntax Error at: %s\n", parser.token->data);
		return (-1);
	}

	return (0);
}
