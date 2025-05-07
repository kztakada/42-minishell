/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_subshell_to_redirect.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 20:31:16 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_loop_status	check_strict_quoting(t_list **next_tokens,
		t_bool *strict_mode)
{
	if (!is_correct_quoting((*next_tokens)->next,
			get_token(*next_tokens)->type))
	{
		*strict_mode = FALSE;
		return (STOP);
	}
	forward_token_list(next_tokens);
	forward_token_list(next_tokens);
	forward_token_list(next_tokens);
	return (CONTINUE);
}

static t_bool	has_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_ifs(str[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static t_loop_status	check_strict_text(t_list **next_tokens)
{
	if (is_ifs(get_token(*next_tokens)->value[0]))
		return (STOP);
	if (has_ifs(get_token(*next_tokens)->value))
		return (STOP);
	forward_token_list(next_tokens);
	return (CONTINUE);
}

int	grammar_subshell_to_redirect(t_list **next_tokens, t_bool *strict_mode)
{
	while (get_token(*next_tokens)->type == OPERAND_TEXT
		|| get_token(*next_tokens)->type == QUOTE_SINGLE
		|| get_token(*next_tokens)->type == QUOTE_DOUBLE)
	{
		if (is_in(QUOTE_DICT, get_token(*next_tokens)))
		{
			if (check_strict_quoting(next_tokens, strict_mode) == STOP)
				return (NG_G);
		}
		else
		{
			if (check_strict_text(next_tokens) == STOP)
				return (OK_G);
		}
	}
	*strict_mode = FALSE;
	return (OK_G);
}
