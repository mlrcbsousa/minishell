/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:10:56 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 09:07:09 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_status.stopped = TRUE;
	if (g_status.pid)
	{
		ft_putstr("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_status.value = 130;
	}
	else
	{
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status.value = 1;
	}
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
	g_status.stopped = TRUE;
	if (g_status.pid)
	{
		ft_putstr("^\\Quit: 3\n");
		rl_redisplay();
		g_status.value = 131;
	}
	else
	{
		ft_putstr("~$ ");
		ft_putstr(rl_line_buffer);
	}
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGSEGV, SIG_IGN);
}
