/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 14:47:06 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	app_init(t_app *self, char *env[])
{
	set_env(self, env);
	g_status.value = 0;
	g_status.stopped = FALSE;
	g_status.pid = 0;
	self->astree = NULL;
	if (tcgetattr(STDIN_FILENO, &(self->term)))
		print_error("tcgetattr", NULL, "error");
	self->term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(self->term)))
		print_error("tcsetattr", NULL, "error");
}

static void	app_destroy(t_app *self)
{
	env_destroy(self);
	self->term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &self->term))
		print_error("tcsetattr", NULL, "error");
}

void	app_loop(t_app *self, char *line)
{
	size_t		size;
	t_stack		analysed;
	t_astree	*astree;

	size = 0;
	analysed = (t_stack){NULL, 0};
	add_history(line);
	size = ft_strlen(line);
	lexical_analysis(line, size, &analysed, self);
	free(line);
	astree = NULL;
	g_status.value = parse(&analysed, &astree);
	if (!analysed.size || g_status.value)
		return ;
	self->astree = astree;
	token_destroy(analysed.token);
	execute_tree(astree, self);
	astree_destroy(astree);
}

/* TODO: make internal exit free all memory
** TODO: make 'exit' show in same line as prompt
** TEST print_tokens(analysed.token);
** printf("successful parsing\n");
** print_astree(astree);
** printf("========================================= NODES END\n"); */
int	main(int argc, char *argv[], char *env[])
{
	t_app	self;
	char	*line;

	app_init(&self, env);
	if (argc > 1)
		g_status.value = script_open(argv[1], &self);
	else
	{
		set_signals();
		while (1)
		{
			line = readline("~$ ");
			if (!line)
			{
				printf("\033[1A");
				printf("\033[3C");
				printf("exit\n");
				break ;
			}
			app_loop(&self, line);
		}
	}
	app_destroy(&self);
	return (g_status.value);
}
