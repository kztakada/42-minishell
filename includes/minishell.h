/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:55:38 by katakada          #+#    #+#             */
/*   Updated: 2025/06/14 03:12:11 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft.h"
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

// for general ***************************************************/
typedef enum e_exit_status		t_exit_status;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}								t_bool;

typedef enum e_binary_result
{
	FAILURE_BIN_R = -1,
	SUCCESS_BIN_R = 0,
}								t_binary_result;

# define FAILURE -1
# define SUCCESS 0
// prompt
# define PROMPT "minishell$ "
# define HEREDOC_PROMPT "> "
# define EXIT_PROMPT "exit\n"

// for signal ***************************************************/
extern volatile sig_atomic_t	g_sig;

// exit status ***************************************************/
enum							e_exit_status
{
	EXIT_S_SUCCESS = 0,
	EXIT_S_FAILURE = 1,
	EXIT_S_SYNTAX_ERROR = 2,
	EXIT_S_CMD_FAILURE = 126,
	EXIT_S_CMD_NOT_FOUND = 127,
	EXIT_S_INVALID_ARG = 128,
	EXIT_S_OUT_OF_RANGE = 255,
};
// error messages *************************************************/
# define TOO_MANY_ARGS "minishell: too many arguments\n"
# define ERROR_MALLOC "Error: Memory allocation failed\n"
# define ERROR_STDREAD "Error: Failed to read STDIN\n"
# define ERROR_OPENDIR "Error: Failed to exec opendir\n"
# define ERROR_OVERTOKEN "Error: Too many Tokens. ID overflow\n"
# define ERROR_EXECVE "Error: Command execution error\n"
# define ERROR_GETCWD "Error: Failed to get current path.\n"
# define ERROR_FORK "Error: Failed to create child process.\n"
# define ERROR_WAITPID "Error: Failed to wait child process.\n"
# define ERROR_PIPE "Error: Failed to generate pipe.\n"
# define ERROR_SYNTAX "minishell: syntax error near unexpected token `"

// for dictionary　************************************************/
// dictionary format: 1st char is separator in the dictionary
# define IFS_DICT "_ _\t_\n" // IFS is Internal Field Separator
# define OPERATORS_DICT " << >> && || | < > ( )"
# define TOKEN_TYPE_DICT " << >> && || | < > ( ) ' \" \n"
# define SPACE_DICT "_ _\t_\n_\v_\f_\r"
# define NUM_DICT " 0 1 2 3 4 5 6 7 8 9"
# define QUOTE_DICT " \" ' "
# define NO_MATCH_DICT "no match in dictionary"
# define INVALID_DICT "invalid dictionary"
# define INVALID_SUBJECT "invalid subject"

typedef struct s_dict_out
{
	t_bool						in_d;
	int							d_index;
	char						*nx_str;
	char						*error;
}								t_dict_out;

// token ************************************************************/
// 	OP_HEREDOC: << OP_APPEND: >> OP_AND: && OP_OR: || OP_PIPE: |
// OP_INPUT: < OP_OUTPUT: > OP_OPEN: ( OP_CLOSE: )
// QUOTE_SINGLE: ' QUOTE_DOUBLE: " TERMINATOR: \n OPERAND_TEXT: identifier
typedef enum e_token_type
{
	OP_HEREDOC,
	OP_APPEND,
	OP_AND,
	OP_OR,
	OP_PIPE,
	OP_INPUT,
	OP_OUTPUT,
	OP_OPEN,
	OP_CLOSE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE,
	TERMINATOR,
	OPERAND_TEXT,
}								t_token_type;

typedef struct s_token			t_token;
struct							s_token
{
	unsigned int				id;
	t_token_type				type;
	char						*value;
};
// t_parsed_word **********************************************
typedef enum e_parsed_word_type
{
	W_PLAIN,
	W_DOUBLE_QUOTED,
	W_SINGLE_QUOTED,
}								t_parsed_word_type;
typedef struct s_parsed_word
{
	t_parsed_word_type			type;
	char						*str;
}								t_parsed_word;
// t_redirection ***********************************************
typedef enum e_redirect_op_type
{
	RE_OP_HEREDOC,
	RE_OP_APPEND,
	RE_OP_INPUT,
	RE_OP_OUTPUT,
}								t_redirect_op_type;
// filename is t_parsed_word list
// if heredoc, filename is EOF
typedef struct s_redirection
{
	t_redirect_op_type			type;
	int							fd;
	t_list						*file_name_words;
	char						*expanded_file_name;
}								t_redirection;
// abs_node ****************************************************
typedef struct s_abs_node		t_abs_node;
typedef enum e_abs_node_type
{
	ABS_BIN_AND,
	ABS_BIN_OR,
	ABS_PIPE,
	ABS_COMMAND,
	ABS_SUBSHELL,
}								t_abs_node_type;
// cmd_words is list of t_parsed_word
// redirections is list of t_redirection
struct							s_abs_node
{
	t_abs_node_type				type;
	t_list						*cmd_words;
	char						**expanded_args;
	t_list						*redirections;
	t_abs_node					*left;
	t_abs_node					*right;
};
// for env    ***************************************************/
typedef struct s_env_var
{
	char						*name;
	char						*value;
}								t_env_var;

typedef struct s_env
{
	t_list						*env_vars;
	t_bool						*unset_oldpwd;
	t_bool						is_interactive;
	t_exit_status				*exit_status;
	int							*line_count;
	t_list						*token_list;
	t_abs_node					*abs_tree;
}								t_env;
//*****************************************************************/

// lexer.c
t_exit_status					lexer(char *input, t_list **token_list);

// parser.c
t_exit_status					parser(t_list *input_tokens,
									t_abs_node **abs_tree, t_env env);

// expander.c
t_exit_status					expander(t_abs_node *abs_tree, t_env env);

// exec.c
void							exec(t_env *env);

// utils **********************************************************/

// dictionary.c
t_dict_out						lookup_dict(char *subject, char *dict);
char							*get_dict_word(int d_index, char *dict);

// free_tools.c
void							free_str_list(char **str_list);
void							no_del(void *target);
void							free_all_env(t_env env);

// util_tools.c
int								is_ifs(char c);
t_list							**forward_token_list(t_list **current_tokens);
char							*strjoin_free(char *s1, char *s2);
void							free_str_list_by_size(char **str_list,
									int str_list_size);
void							ft_swap(void **a, void **b);

// lexing_utils.c
void							free_token(void *target);

// dialog_minishell.c
void							dialog_minishell(t_env env);
void							execute_command(char *input, t_env env);

// init_env__shlvl.c
t_binary_result					init_env_shlvl(t_list **env_list);
t_bool							has_numeric_chars(const char *str);
t_bool							has_only_numbers(const char *str);

// init_env__utils.c
void							free_env_var(void *env_var);
t_env_var						*copy_deep_env_var(t_env_var *env_var);

// init_env.c
t_list							*init_envlst(char **env);
t_env_var						*get_env_var(char *env_var_source);
t_list							**set_env_var_to_list(t_list **env_vars,
									t_env_var *env_var);

// parser_utils.c
void							free_abs_tree(t_abs_node *abs_tree);

// env_utils
int								is_env_exist(t_list *env_list, char *name);
int								create_add_new_env(t_list **env_list,
									char *name, char *value);
int								update_env_value(t_list **env_list, char *name,
									char *value);
char							*get_env_value(t_list *env_vars, char *name);

// clean_and_exit.c
void							clean_and_exit(int exit_status, t_env *env);

#endif