/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:25 by katakada          #+#    #+#             */
/*   Updated: 2025/04/05 17:24:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "minishell.h"

# define PROMPT "minishell$ "

// for parse
typedef enum e_node_type
{
	N_PIPE,
	N_AND,
	N_OR,
	N_CMD
}						t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}						t_io_type;

typedef enum e_parse_err_type
{
	E_MEM = 1,
	E_SYNTAX
}						t_parse_err_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_io_node	*prev;
	struct s_io_node	*next;
}						t_io_node;

typedef struct s_node
{
	t_node_type			type;
	t_io_node			*io_list;
	char				*args;
	char				**expanded_args;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef enum e_parse_error_code
{
	PARSE_NO_ERROR = 0,
	PARSE_UNEXPECTED_TOKEN,
	PARSE_UNEXPECTED_EOF,
	PARSE_UNMATCHED_PARENTHESIS,
	PARSE_INVALID_SYNTAX,
}						t_parse_error_code;

typedef struct s_parse_error
{
	t_parse_error_code	code;
	int					line;
	int					column;
}						t_parse_error;

// for tokenize
typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*str;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

#endif