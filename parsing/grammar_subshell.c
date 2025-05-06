/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:03:18 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 00:34:16 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
#define NG_NEXT_TO_S_OPEN " ) && || | \n"
#define NG_NEXT_TO_S_CLOSE " ( ' \""

int	grammar_sub_open(t_list **next_tokens, int *subshell_depth)
{
	if (is_in(NG_NEXT_TO_S_OPEN, get_token(*next_tokens)))
		return (NG);
	(*subshell_depth)++;
	return (OK);
}

int	grammar_sub_close(t_list **next_tokens, int *subshell_depth)
{
	if (*subshell_depth == 0)
		return (NG);
	if (is_in(NG_NEXT_TO_S_CLOSE, get_token(*next_tokens)))
		return (NG);
	if (is_operand_text(get_token(*next_tokens)))
		return (NG);
	if (*subshell_depth == 1 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG);
	(*subshell_depth)--;
	return (OK);
}

// terminator
int	grammar_terminator(t_list **next_tokens, int *subshell_depth)
{
	(void)next_tokens;
	if (*subshell_depth > 0)
		return (NG);
	return (OK);
}
