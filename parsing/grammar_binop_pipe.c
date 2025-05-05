/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_binop_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:01:41 by katakada          #+#    #+#             */
/*   Updated: 2025/05/05 19:09:55 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
#define NG_NEXT_TO_PIPE " && || | ) \n"
#define NG_NEXT_TO_B_AND " && || | ) \n"
#define NG_NEXT_TO_B_OR " && || | ) \n"

// " << >> && || | < > ( ) ' \" \n"

// binary operators
int	grammar_binop_and(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_B_AND, get_token(*next_tokens)))
		return (NG);
	return (OK);
}

int	grammar_binop_or(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_B_OR, get_token(*next_tokens)))
		return (NG);
	return (OK);
}

// pipe
int	grammar_pipe(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_PIPE, get_token(*next_tokens)))
		return (NG);
	return (OK);
}
