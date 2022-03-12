/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:10:56 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 01:55:38 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(t_app *self)
{
	self->sigint_handler = signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
}
