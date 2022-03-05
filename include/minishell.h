/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:16:34 by msousa            #+#    #+#             */
/*   Updated: 2022/03/05 18:32:17 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef DEBUG_MODE
#  define DEBUG(x) x
# else
#  define DEBUG(x)
# endif

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

# include "libft.h"

// Enums
typedef enum e_node {
	NODE_PIPE = 1, // have to start at one to not override in astree_set_data()
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_CMDPATH,
	NODE_ARGUMENT,
	NODE_DATA,
} t_node;

enum e_lexical {
	LEXICAL_DEFAULT = -1,
	LEXICAL_PIPE = '|',
	LEXICAL_QUOTE = '\'',
	LEXICAL_DQUOTE = '\"',
	LEXICAL_WHITESPACE = ' ',
	LEXICAL_ESCAPESEQUENCE = '\\',
	LEXICAL_GREATER = '>',
	LEXICAL_LESSER = '<',
	LEXICAL_NULL = 0,
};

enum e_state {
	STATE_DQUOTE,
	STATE_QUOTE,
	STATE_ESCAPESEQ,
	STATE_DEFAULT,
};

// Structs & Types
typedef struct s_app t_app; // main app state
typedef struct s_token t_token; // typed linked list for tokens
typedef struct s_stack t_stack; // stack to store tokens
typedef struct s_lexer t_lexer; // main lexer state
typedef struct s_astree t_astree; // typed binary tree for BNF
typedef struct s_parser t_parser; // main parser state
typedef struct s_executor t_executor; // main executor state
typedef struct s_command t_command; // command info
typedef struct s_builtin_def t_builtin_def;
typedef int	(t_builtin)(t_command *command, t_app *self);

struct s_app
{
	char	**env;
	void	(*sigint_handler)(int);
	t_astree *astree;
};

struct s_token
{
	int type;
	char *data;
	t_token *next;
};

struct s_stack
{
	t_token *token;
	int size;
};

struct s_lexer
{
	t_token *token;
	int state;
	int size;
	int line_i;
	int data_i;
	char c;
	int type;
};

struct s_astree
{
	int type;
	char *data;
	t_astree *left;
	t_astree *right;
};

struct s_parser
{
	t_token	*current_token;
};

struct s_executor
{
	t_bool stdin_pipe;
	t_bool stdout_pipe;
	int pipe_read;
	int pipe_write;
	char* redirect_in;
	char* redirect_out;
};

struct s_command
{
	int argc;
	char **argv;
	t_bool stdin_pipe;
	t_bool stdout_pipe;
	int pipe_read;
	int pipe_write;
	char* redirect_in;
	char* redirect_out;
};

struct	s_builtin_def
{
	char		*name;
	t_builtin	*builtin;
};

// Functions //

// token
void token_init(t_token *token, int size);
void token_destroy(t_token *token);
int tokens_length(t_token *token);

// lexer
void	lexical_analysis(char *line, int size, t_stack *tokens);
int	lexical_type(char token);
void	lexer_end_read_token(t_lexer *lexer);
void	lexer_type_quote(t_lexer *lexer);
void	lexer_type_dquote(t_lexer *lexer);
void	lexer_type_default(t_lexer *lexer);
void	lexer_type_operator(t_lexer *lexer);

// abstract syntax tree
void astree_add_branches(t_astree *root , t_astree *left , t_astree *right);
void astree_set_type(t_astree *node , t_node type);
void astree_set_data(t_astree *node , char *data);
void astree_destroy(t_astree *node);

// BNF parser
int parse(t_stack *analysed, t_astree **astree);
t_bool	match(int token_type, char **buffer, t_parser *parser);
t_astree* command_line(t_parser *parser);
t_astree* command_line_a(t_parser *parser);
t_astree* command(t_parser *parser);
t_astree* command_a(t_parser *parser);
t_astree* command_b(t_parser *parser);
t_astree* simple_command(t_parser *parser);
t_astree* token_list(t_parser *parser);
t_astree	*token_list_a(t_parser *parser);

// utils
void sigint_handler(int sig);

// env
char	**get_binary_paths(void);
void	find_binary_path(t_command *command);

// execute
void	execute_tree(t_astree *node, t_app *self);
void	command_init(t_astree *node, t_command *command, t_executor executor);
void	command_execute(t_command *command, t_app *self);
void	command_destroy(t_command *command);

// builtins
t_builtin	*get_builtin(char *cmd_path);
int	builtin_echo(t_command *command, t_app *self);
int	builtin_cd(t_command *command, t_app *self);
int	builtin_pwd(t_command *command, t_app *self);
int	builtin_export(t_command *command, t_app *self);
int	builtin_unset(t_command *command, t_app *self);
int	builtin_env(t_command *command, t_app *self);
int	builtin_exit(t_command *command, t_app *self);

// run
void	run(t_command *command, t_app *self);
void	run_setup_io(t_command *command);
void	run_setup_pipes(t_command *command);
void	run_setup_pipe_read(t_command *command);
void	run_setup_pipe_write(t_command *command);
void	run_setup_redirects(t_command *command);
void	run_setup_redirect_in(t_command *command);
void	run_setup_redirect_out(t_command *command);

#endif
