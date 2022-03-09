/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 19:13:33 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_parser	t_parser;
typedef struct s_astree	t_astree;

/* BNF parser */
t_astree	*command_line(t_parser *parser);
t_astree	*command_line_a(t_parser *parser);
t_astree	*command(t_parser *parser);
t_astree	*command_a(t_parser *parser);
t_astree	*command_b(t_parser *parser);
t_astree	*command_c(t_parser *parser);
t_astree	*command_d(t_parser *parser);
t_astree	*redirect_command(t_parser *parser);
t_astree	*redirect_command_a(t_parser *parser);
t_astree	*redirect_command_b(t_parser *parser);
t_astree	*redirect_command_c(t_parser *parser);
t_astree	*redirect_command_d(t_parser *parser);
t_astree	*simple_command(t_parser *parser);
t_astree	*token_list(t_parser *parser);
t_astree	*token_list_a(t_parser *parser);

#endif
