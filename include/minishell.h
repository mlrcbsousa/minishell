/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/03/09 18:42:21 by msousa           ###   ########.fr       */
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

# include "libft.h"

// Constants
# define EXPAND_DOLLAR '$'
# define EXPAND_QUESTION '?'
# define EXPAND_USCORE '_'

// Global
int	g_return;

// Enums
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

// Structs & Types
typedef struct s_app	t_app; // main app state
typedef struct s_token	t_token; // typed linked list for tokens
typedef struct s_stack	t_stack; // stack to store tokens
typedef struct s_lexer	t_lexer; // main lexer state
typedef struct s_astree	t_astree; // typed binary tree for BNF
typedef struct s_parser	t_parser; // main parser state
typedef struct s_executor	t_executor; // main executor state
typedef struct s_command	t_command; // command info
typedef struct s_builtin_def	t_builtin_def;
typedef struct s_env	t_env;
typedef struct s_io	t_io;

typedef int (t_builtin)(t_command *command, t_app *self);

struct s_app
{
	t_env		*env;
	char		**env_raw;
	void		(*sigint_handler)(int);
	t_astree	*astree;
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

struct s_executor
{
	t_bool	stdin_pipe;
	t_bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_io	*redirect_in;
	t_io	*redirect_out;
};

struct s_command
{
	int		argc;
	char	**argv;
	t_bool	stdin_pipe;
	t_bool	stdout_pipe;
	int		pipe_read;
	int		pipe_write;
	t_io	*redirect_in;
	t_io	*redirect_out;
};

struct	s_builtin_def
{
	char		*name;
	t_builtin	*builtin;
};

// Functions //

// token
void	token_init(t_token *token, int size);
void	token_destroy(t_token *token);
int		tokens_length(t_token *token);

// lexer
void	lexical_analysis(char *line, int size, t_stack *analysed, t_env *env);
int		lexical_type(char token);
void	lexer_end_read_token(t_lexer *lexer);
void	lexer_type_quote(t_lexer *lexer);
void	lexer_type_dquote(t_lexer *lexer);
void	lexer_type_default(t_lexer *lexer);
void	lexer_type_operator(t_lexer *lexer);
void	lexer_expand(t_token *token, t_env *env);

// abstract syntax tree
void	astree_add_branches(t_astree *root, t_astree *left, t_astree *right);
void	astree_set_type(t_astree *node, t_node type);
void	astree_set_data(t_astree *node, char *data);
void	astree_destroy(t_astree *node);

// BNF parser
int		parse(t_stack *analysed, t_astree **astree);
t_bool	match(int token_type, char **buffer, t_parser *parser);

// utils
void	sigint_handler(int sig);
void	ft_free_string_arrays(char **array);
char	**ft_split_first(char const *s, char c);
char	*get_env(char *key, t_env *env);
int		is_valid_identifier(char *str);
char	*get_expanded(char *raw, t_env *env);
char	*get_stripped(char *src);

// env
char	**get_binary_paths(t_env *env);
void	find_binary_path(t_command *command, t_env *env);
char	**get_env_raw(t_app *self);
void	set_env(t_app *self, char **raw);
void	env_destroy(t_app *self);
t_env	*env_create(char *raw);

// redirect
t_io	*redirect_last(t_io *io);
void	redirect_add_back(t_io **io, t_io *new);
void	redirect_clear(t_io **io);

// execute
void	execute_tree(t_astree *node, t_app *self);
void	command_init(t_astree *node, t_command *command, t_executor executor);
void	command_execute(t_command *command, t_app *self);
void	command_destroy(t_command *command);

// builtins
t_builtin	*get_builtin(char *cmd_path);
int		builtin_echo(t_command *command, t_app *self);
int		builtin_cd(t_command *command, t_app *self);
int		builtin_pwd(t_command *command, t_app *self);
int		builtin_export(t_command *command, t_app *self);
int		builtin_unset(t_command *command, t_app *self);
int		builtin_env(t_command *command, t_app *self);
int		builtin_exit(t_command *command, t_app *self);

// run
void	run(t_command *command, t_app *self);
void	run_setup_io(t_command *command, t_env *env);
void	run_setup_io_in(t_io *io, t_env *env);
void	run_setup_io_out(t_io *io);
void	run_setup_redirect_in(t_io *io);
void	run_setup_redirect_out(t_io *io);
void	run_setup_heredoc(t_io *io, t_env *env);
void	run_setup_append(t_io *io);

// test
void	print_astree(t_astree *node);
void	print_tokens(t_token *token);
void	print_command(t_command *command);

#endif
