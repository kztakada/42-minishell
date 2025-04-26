/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:25 by katakada          #+#    #+#             */
/*   Updated: 2025/04/26 23:29:49 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "../libraries/libft.h"
# include "lexing.h"
# include "minishell.h"

# define PROMPT "minishell$ "

# define FAILURE -1
# define SUCCESS 0

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

// parse.c
t_abs_node					*parse(t_token *token_list);

#endif
