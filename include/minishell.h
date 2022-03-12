/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/03/12 15:21:33 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <termios.h>

# include "libft.h"
# include "parser.h"
# include "builtin.h"

/* Constants */
# define EXPAND_DOLLAR '$'
# define EXPAND_QUESTION '?'
# define EXPAND_USCORE '_'

/* Enums */
typedef enum e_node
{
	NODE_PIPE = 1,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_HEREDOC,
	NODE_APPEND,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_DATA,
}	t_node;

enum e_lexical {
	LEXICAL_DEFAULT = -1,
	LEXICAL_PIPE = '|',
	LEXICAL_QUOTE = '\'',
	LEXICAL_DQUOTE = '\"',
	LEXICAL_WHITESPACE = ' ',
	LEXICAL_GREATER = '>',
	LEXICAL_GGREATER = -2,
	LEXICAL_LESSER = '<',
	LEXICAL_LLESSER = -3,
	LEXICAL_NULL = 0,
};

enum e_state {
	STATE_DQUOTE,
	STATE_QUOTE,
	STATE_ESCAPESEQ,
	STATE_DEFAULT,
};

/* Structs & Types & Global */
typedef struct s_app	t_app;
typedef struct s_token	t_token;
typedef struct s_stack	t_stack;
typedef struct s_lexer	t_lexer;
typedef struct s_astree	t_astree;
typedef struct s_parser	t_parser;
typedef struct s_env	t_env;
typedef struct s_io		t_io;
typedef struct s_status	t_status;
t_status				g_status;

struct s_app
{
	t_env			*env;
	char			**env_raw;
	t_astree		*astree;
	struct termios	term;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

struct s_token
{
	int		type;
	char	*data;
	t_token	*next;
};

struct s_stack
{
	t_token	*token;
	int		size;
};

struct s_lexer
{
	t_token	*token;
	int		state;
	int		size;
	char	*line;
	int		line_i;
	int		data_i;
	char	c;
	int		type;
};

struct s_astree
{
	int			type;
	char		*data;
	t_astree	*left;
	t_astree	*right;
};

struct s_parser
{
	t_token	*current_token;
};

struct s_io
{
	int		type;
	char	*data;
	t_io	*next;
};

typedef struct s_executor
{
	t_bool	stdin_pipe;
	t_bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_io	*redirect_in;
	t_io	*redirect_out;
}	t_executor;

typedef struct s_command
{
	int		argc;
	char	**argv;
	t_bool	stdin_pipe;
	t_bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_io	*redirect_in;
	t_io	*redirect_out;
}	t_command;

struct	s_bin_def
{
	char	*name;
	t_bin	*builtin;
};

struct	s_status
{
	int		value;
	t_bool	stopped;
	pid_t	pid;
};

/* Functions */

/* main */
void	app_loop(t_app *self, char *line);
int		script_open(char *filename, t_app *self);
int		script_read(int fd, t_app *self);

/* token */
void	token_init(t_token *token, int size);
void	token_destroy(t_token *token);
int		tokens_length(t_token *token);

/* lexer */
void	lexical_analysis(char *line, int size, t_stack *analysed, t_app *self);
int		lexical_type(char token);
void	lexer_end_read_token(t_lexer *lexer);
void	lexer_type_quote(t_lexer *lexer);
void	lexer_type_dquote(t_lexer *lexer);
void	lexer_type_default(t_lexer *lexer);
void	lexer_type_operator(t_lexer *lexer);
void	lexer_type_null(t_lexer *lexer);
void	lexer_expand(t_token *token, t_app *self);

/* abstract syntax tree */
void	astree_add_branches(t_astree *root, t_astree *left, t_astree *right);
void	astree_set_type(t_astree *node, t_node type);
void	astree_set_data(t_astree *node, char *data);
void	astree_destroy(t_astree *node);

/* BNF parser */
int		parse(t_stack *analysed, t_astree **astree);
t_bool	match(int token_type, char **buffer, t_parser *parser);

/* signals */
void	set_signals(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

/* utils */
void	ft_free_string_arrays(char **array);
char	**ft_split_first(char const *s, char c);
char	*get_env(char *key, t_env *env);
int		is_valid_identifier(char *str);
char	*get_expanded(char *raw, t_app *self);
char	*get_stripped(char *src);

/* env */
char	**get_binary_paths(t_env *env);
void	find_binary_path(t_command *command, t_env *env);
char	**get_env_raw(t_app *self);
void	set_env(t_app *self, char **raw);
void	env_destroy(t_app *self);
t_env	*env_create(char *raw);

/* redirect */
t_io	*redirect_last(t_io *io);
void	redirect_add_back(t_io **io, t_io *new);
void	redirect_clear(t_io **io);

/* execute */
void	execute_tree(t_astree *node, t_app *self);
void	execute_simple_command(t_astree *simple_command_node,
			t_executor executor, t_app *self);
void	command_init(t_astree *node, t_command *command, t_executor executor);
void	command_execute(t_command *command, t_app *self);
void	command_destroy(t_command *command);

/* builtins */
int		builtin_echo(t_command *command, t_app *self);
int		builtin_cd(t_command *command, t_app *self);
int		builtin_pwd(t_command *command, t_app *self);
int		builtin_export(t_command *command, t_app *self);
int		builtin_unset(t_command *command, t_app *self);
int		builtin_env(t_command *command, t_app *self);
int		builtin_exit(t_command *command, t_app *self);

/* run */
int		run(t_command *command, t_app *self);
void	run_setup_io(t_command *command, t_app *self);
void	run_setup_io_in(t_io *io, t_app *self);
void	run_setup_io_out(t_io *io);
void	run_setup_redirect_in(t_io *io);
void	run_setup_redirect_out(t_io *io);
void	run_setup_heredoc(t_io *io, t_app *self);
void	run_setup_append(t_io *io);

/* helpers */
void	free_memory(t_app *self, t_command *command);
void	print_error(char *cmd, char *input, char *msg);
void	print_errno(char *cmd, char *input);

/* test */
void	print_astree(t_astree *node);
void	print_tokens(t_token *token);
void	print_command(t_command *command);

#endif
