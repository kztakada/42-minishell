/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 01:01:21 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:26:54 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define NG_NEXT_TO_QUOTE " ("

t_bool	is_correct_quoting(t_list *next_to_quote_tokens,
		t_token_type quote_token_type)
{
	if (next_to_quote_tokens == NULL || next_to_quote_tokens->content == NULL)
		return (FALSE);
	if (get_token(next_to_quote_tokens)->type != OPERAND_TEXT)
		return (FALSE);
	if (get_token((next_to_quote_tokens)->next)->type != quote_token_type)
		return (FALSE);
	else
		return (TRUE);
}

int	grammar_quote_single(t_list **next_tokens, int subshell_depth)
{
	(void)subshell_depth;
	if (get_token(*next_tokens)->type != OPERAND_TEXT)
		return (NG_G);
	else if (is_correct_quoting(*next_tokens, QUOTE_SINGLE) == FALSE)
	{
		*next_tokens = (*next_tokens)->next;
		return (NG_G);
	}
	else
		*next_tokens = (*next_tokens)->next->next;
	if (is_in(NG_NEXT_TO_QUOTE, get_token(*next_tokens)))
		return (NG_G);
	if (subshell_depth == 0 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG_G);
	return (OK_G);
}

int	grammar_quote_double(t_list **next_tokens, int subshell_depth)
{
	(void)subshell_depth;
	if (get_token(*next_tokens)->type != OPERAND_TEXT)
		return (NG_G);
	else if (is_correct_quoting(*next_tokens, QUOTE_DOUBLE) == FALSE)
	{
		*next_tokens = (*next_tokens)->next;
		return (NG_G);
	}
	else
		*next_tokens = (*next_tokens)->next->next;
	if (is_in(NG_NEXT_TO_QUOTE, get_token(*next_tokens)))
		return (NG_G);
	if (subshell_depth == 0 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG_G);
	return (OK_G);
}
