/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_binop_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:01:41 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 20:29:48 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
#define NG_NEXT_TO_PIPE " && || | ) \n"
#define NG_NEXT_TO_B_AND " && || | ) \n"
#define NG_NEXT_TO_B_OR " && || | ) \n"

// " << >> && || | < > ( ) ' \" \n"

// binary operators
int	grammar_binop_and(t_list **next_tokens, int subshell_depth)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_B_AND, get_token(*next_tokens)))
		return (NG_G);
	return (OK_G);
}

int	grammar_binop_or(t_list **next_tokens, int subshell_depth)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_B_OR, get_token(*next_tokens)))
		return (NG_G);
	return (OK_G);
}

// pipe
int	grammar_pipe(t_list **next_tokens, int subshell_depth)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_PIPE, get_token(*next_tokens)))
		return (NG_G);
	return (OK_G);
}
