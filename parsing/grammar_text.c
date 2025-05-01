/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:44 by katakada          #+#    #+#             */
/*   Updated: 2025/05/02 01:46:41 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

#define NG_NEXT_TO_O_TEXT " ("

// " << >> && || | < > ( ) ' \" \n"

int	grammar_quote_single(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (get_token(*next_tokens)->type == TERMINATOR)
		return (NG);
	if (get_token(*next_tokens)->type != OPERAND_TEXT)
		return (NG);
	if (get_token((*next_tokens)->next)->type != QUOTE_SINGLE)
	{
		*next_tokens = (*next_tokens)->next;
		return (NG);
	}
	else
		*next_tokens = (*next_tokens)->next->next;
	if (is_in(NG_NEXT_TO_O_TEXT, get_token(*next_tokens)))
		return (NG);
	if (subshell_count == 0 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG);
	return (OK);
}

int	grammar_quote_double(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (get_token(*next_tokens)->type == TERMINATOR)
		return (NG);
	if (get_token(*next_tokens)->type != OPERAND_TEXT)
		return (NG);
	if (get_token((*next_tokens)->next)->type != QUOTE_DOUBLE)
	{
		*next_tokens = (*next_tokens)->next;
		return (NG);
	}
	else
		*next_tokens = (*next_tokens)->next->next;
	if (is_in(NG_NEXT_TO_O_TEXT, get_token(*next_tokens)))
		return (NG);
	if (subshell_count == 0 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG);
	return (OK);
}

int	grammar_operand_text(t_token *testing_token, t_list **next_tokens,
		int subshell_count)
{
	(void)testing_token;
	if (is_in(NG_NEXT_TO_O_TEXT, get_token(*next_tokens)))
		return (NG);
	if (subshell_count == 0 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG);
	return (OK);
}
