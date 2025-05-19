/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:55:38 by katakada          #+#    #+#             */
/*   Updated: 2025/05/19 21:48:10 by katakada         ###   ########.fr       */
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
# include <sys/wait.h>
# include <termios.h>

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
// for env    ***************************************************/
typedef struct s_env_var
{
	char					*name;
	char					*value;
}							t_env_var;

typedef struct s_env
{
	t_list					*env_vars;
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
};
// error messages *************************************************/
# define ERROR_MALLOC "Error: Memory allocation failed\n"
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
//*****************************************************************/

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

// lexing_utils.c
void						free_token(void *target);
#endif