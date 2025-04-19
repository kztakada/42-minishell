/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:25 by katakada          #+#    #+#             */
/*   Updated: 2025/04/19 23:00:07 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "../libraries/libft.h"
# include "minishell.h"

# define PROMPT "minishell$ "

# define FAILURE -1

// for parse

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}							t_parse_err_type;

// コンテントリスト


// 2分木構造
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	B_OP_AND,
	B_OP_OR,
	B_OP_PIPE,
	REDIRECT,
	COMMAND
}							t_abs_node_type;

typedef enum e_io_cmd_type
{
	IO_HEREDOC,
	IO_APPEND,
	IO_IN,
	IO_OUT
}							t_io_cmd_type;
typedef struct s_io_cmd
{
	t_io_cmd_type			cmd_type;
	char					*value;
	char					**expanded_value;
	int						here_doc;
}							t_io_cmd;

struct						s_abs_node
{
	t_abs_node_type			node_type;
	t_list					*io_cmd_list;
	char					*cmd_args;
	char					**expanded_args;
	t_abs_node				*left;
	t_abs_node				*right;
};

typedef enum e_parse_error_code
{
	PARSE_NO_ERROR = 0,
	PARSE_UNEXPECTED_TOKEN,
	PARSE_UNEXPECTED_EOF,
	PARSE_UNMATCHED_PARENTHESIS,
	PARSE_INVALID_SYNTAX,
}							t_parse_error_code;

typedef struct s_parse_error
{
	t_parse_error_code		code;
	int						line;
	int						column;
}							t_parse_error;

// for tokenize
typedef enum e_token_type
{
	OP_HEREDOC,         // <<
	OP_APPEND_REDIRECT, // >>
	OP_AND,             // &&
	OP_OR,              // ||
	OP_PIPE,            // |
	OP_INPUT_REDIRECT,  // <
	OP_OUTPUT_REDIRECT, // >
	OP_OPEN_SUBSHELL,   // (
	OP_CLOSE_SUBSHELL,  // )
	TERMINATOR,         // \n
	OPERAND_TEXT,       // identifier
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*content;
}							t_token;

// tokenize.c
t_list						*tokenize(char *input);
void						delete_token(void *target);

// parse.c
t_abs_node					*parse(t_token *token_list);

#endif
