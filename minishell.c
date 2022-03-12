/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 17:09:14 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 02:08:39 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	app_init(t_app *self, char *env[])
{
	set_env(self, env);
	self->astree = NULL;
	self->status = 0;
	if (!tcgetattr(STDIN_FILENO, &self->term))
		print_error("tcgetattr", NULL, "error");
	self->term.c_lflag &= ~ECHOCTL;
	if (!tcsetattr(STDIN_FILENO, TCSANOW, &self->term))
		print_error("tcsetattr", NULL, "error");
}

static void	app_destroy(t_app *self)
{
	env_destroy(self);
	self->term.c_lflag |= ECHOCTL;
	if (!tcsetattr(STDIN_FILENO, TCSANOW, &self->term))
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
	free(line); // line = NULL;
	astree = NULL;
	self->status = parse(&analysed, &astree);
	if (!analysed.size || self->status)
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
	t_app		self;
	char		*line;

	// self = (t_app){0, 0, 0, 0, 0, NULL};
	app_init(&self, env);
	if (argc > 1)
	{
		self.status = script_open(argv[1], &self);
		return (self.status);
	}
	set_signals(&self);
	while (1)
	{
		line = readline("~$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		app_loop(&self, line);
	}
	app_destroy(&self);
	return (self.status);
}
