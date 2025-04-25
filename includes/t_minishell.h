/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:25 by katakada          #+#    #+#             */
/*   Updated: 2025/04/25 19:27:50 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "../libraries/libft.h"
# include "minishell.h"

# define PROMPT "minishell$ "

# define FAILURE -1
# define SUCCESS 0

// for tokenize
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
	TERMINATOR,   // \n
	OPERAND_TEXT, // identifier
}							t_token_type;

typedef struct s_token		t_token;
struct						s_token
{
	t_token_type			type;
	char					*content;
};

// for parse

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}							t_parse_err_type;

typedef struct s_env_var
{
	char					*name;
	char					*value;
}							t_env_var;

// コンテントリスト

// 2分木構造
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	BINARY_OP,
	REDIRECT,
	SUBSHELL,
	COMMAND
}							t_abs_node_type;

typedef struct s_redirection
{
	char					*value;
	char					**expanded_value;
	int						here_doc;
}							t_redirection;

struct						s_abs_node
{
	t_abs_node_type			node_type;
	t_token					*token;
	t_list					*redirection_list;
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

// tokenize.c
t_list						*lexer(char *input);
void						delete_token(void *target);

// parse.c
t_abs_node					*parse(t_token *token_list);

#endif
