/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:55:38 by katakada          #+#    #+#             */
/*   Updated: 2025/06/02 04:40:32 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libraries/libft.h"
# include "./for_test.h" // for test
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
typedef enum e_exit_status	t_exit_status;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}							t_bool;

typedef enum e_binary_result
{
	FAILURE_BIN_R = -1,
	SUCCESS_BIN_R = 0,
}							t_binary_result;

# define FAILURE -1
# define SUCCESS 0
// prompt
# define PROMPT "minishell$ "
# define HEREDOC_PROMPT "> "
// for env    ***************************************************/
typedef struct s_env_var
{
	char					*name;
	char					*value;
}							t_env_var;

typedef struct s_env
{
	t_list					*env_vars;
	t_bool					*unset_oldpwd;
	t_exit_status			*exit_status;
}							t_env;
// exit status ***************************************************/
enum						e_exit_status
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
# define ERROR_MALLOC "Error: Memory allocation failed\n"
# define ERROR_EXECVE "Error: Execve function error\n"
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
	t_bool					in_d;
	int						d_index;
	char					*nx_str;
	char					*error;
}							t_dict_out;

// token ************************************************************/
typedef enum e_token_type
{
	OP_HEREDOC,   // <<
	OP_APPEND,    // >>
	OP_AND,       // &&
	OP_OR,        // ||
	OP_PIPE,      // |
	OP_INPUT,     // <
	OP_OUTPUT,    // >
	OP_OPEN,      // (
	OP_CLOSE,     // )
	QUOTE_SINGLE, // '
	QUOTE_DOUBLE, // "
	TERMINATOR,   // \n
	OPERAND_TEXT, // identifier
}							t_token_type;

typedef struct s_token		t_token;
struct						s_token
{
	unsigned int			id;
	t_token_type			type;
	char					*value;
};
// t_parsed_word **********************************************
typedef enum e_parsed_word_type
{
	W_PLAIN,
	W_DOUBLE_QUOTED,
	W_SINGLE_QUOTED,
}							t_parsed_word_type;
typedef struct s_parsed_word
{
	t_parsed_word_type		type;
	char					*str;
}							t_parsed_word;
// t_redirection ***********************************************
typedef enum e_redirect_op_type
{
	RE_OP_HEREDOC,
	RE_OP_APPEND,
	RE_OP_INPUT,
	RE_OP_OUTPUT,
}							t_redirect_op_type;
// filename is t_parsed_word list
// if heredoc, filename is EOF
typedef struct s_redirection
{
	t_redirect_op_type		type;
	int						fd;
	t_list					*file_name_words;
	char					*expanded_file_name;
}							t_redirection;
// abs_node ****************************************************
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	ABS_BIN_AND,
	ABS_BIN_OR,
	ABS_PIPE,
	ABS_COMMAND
}							t_abs_node_type;
// cmd_words is list of t_parsed_word
// redirections is list of t_redirection
struct						s_abs_node
{
	t_bool					is_subshell;
	t_abs_node_type			type;
	t_list					*cmd_words;
	char					**expanded_args;
	t_list					*redirections;
	t_abs_node				*left;
	t_abs_node				*right;
};
//*****************************************************************/

// lexer.c
t_exit_status				lexer(char *input, t_list **token_list);

// parser.c
t_exit_status				parser(t_list *input_tokens, t_abs_node **abs_tree,
								t_env env);

// expander.c
t_exit_status				expander(t_abs_node *abs_tree, t_env env);

// exec.c
void						exec(t_abs_node *abs_tree, t_env *env);

// utils **********************************************************/

// dictionary.c
t_dict_out					lookup_dict(char *subject, char *dict);
char						*get_dict_word(int d_index, char *dict);

// free_tools.c
void						free_str_list(char **str_list);
void						no_del(void *target);
;

// util_tools.c
int							is_ifs(char c);
t_list						**forward_token_list(t_list **current_token_list);
char						*strjoin_free(char *s1, char *s2);
void						free_str_list_by_size(char **str_list,
								int str_list_size);
void						ft_swap(void **a, void **b);

// lexing_utils.c
void						free_token(void *target);

// init_env__utils.c
void						free_env_var(void *env_var);

// init_env.c
t_list						*init_envlst(char **env);

// parser_utils.c
void						free_abs_tree(t_abs_node *abs_tree);

// env_utils
int				is_env_exist(t_list *env_list, char *name);
char			*get_env_value(t_list *env_vars, char *name);

// err_msg (std_lib_func)
int				err_msg_malloc(void);
int				err_msg_execve(void);

#endif