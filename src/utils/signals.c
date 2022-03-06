#include "minishell.h"

void sigint_handler(int sig) {
	// TODO kill a running process

	// This clears the readline input
	if(sig == SIGINT) {
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
