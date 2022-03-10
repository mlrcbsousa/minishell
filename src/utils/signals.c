/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:10:56 by msousa            #+#    #+#             */
/*   Updated: 2022/03/10 03:00:32 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	// if (sig != SIGINT)
	// 	return ;
	(void)sig;
	printf("\n");
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
