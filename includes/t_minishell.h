/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:25 by katakada          #+#    #+#             */
/*   Updated: 2025/05/15 17:31:10 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "../libraries/libft.h"
# include "minishell.h"
# include "parsing.h"

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



// typedef struct s_redirect
// {
// 	char					*value;
// 	char					**expanded_value;
// 	int						here_doc;
// }							t_redirect;



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

#endif
