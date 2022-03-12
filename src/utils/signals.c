/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:10:56 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 04:13:24 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handle_sigint(void)
// {
// 	ft_putchar('\n');
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	if (g_mini.pid)
// 	{
// 		ft_putstr("^C\n");
// 		g_mini.status = 130;
// 	}
// 	else
// 	{
// 		g_mini.status = 1;
// 		rl_redisplay();
// 	}
// }

// void	handle_sigquit(void)
// {
// 	if (g_mini.pid)
// 	{
// 		ft_putstr("^\\Quit: 3\n");
// 		g_mini.status = 131;
// 		rl_redisplay();
// 	}
// 	else
// 	{
// 		ft_putstr(g_mini.prompt);
// 		ft_putstr(rl_line_buffer);
// 	}
// }

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	// ft_putchar('\n');
	// rl_replace_line("", 0);
	// rl_on_new_line();
	if (g_status.pid)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr("^C\n");
		g_status.value = 130;
	}
	else
	{
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		g_status.value = 1;
		rl_redisplay();
	}
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return ;
	if (g_status.pid)
	{
		g_status.value = 131;
		ft_putstr("^\\Quit: 3\n");
		rl_redisplay();
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
