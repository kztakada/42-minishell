/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:01:34 by katakada          #+#    #+#             */
/*   Updated: 2025/05/05 02:12:19 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
#define NG_NEXT_TO_HEREDOC " << >> && || | < > ( )"
#define NG_NEXT_TO_R_INPUT " << >> && || | < > ( )"
#define NG_NEXT_TO_R_OUTPUT " << >> && || | < > ( )"
#define NG_NEXT_TO_R_APPEND " << >> && || | < > ( )"

// " << >> && || | < > ( ) ' \" \n"

int	grammar_heredoc(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_HEREDOC, get_token(*next_tokens)))
		return (NG);
	if (get_token(*next_tokens)->type == TERMINATOR)
		return (NG);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG);
	return (OK);
}

int	grammar_re_append(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_R_APPEND, get_token(*next_tokens)))
		return (NG);
	if (get_token(*next_tokens)->type == TERMINATOR)
		return (NG);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG);
	return (OK);
}

int	grammar_re_input(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_R_INPUT, get_token(*next_tokens)))
		return (NG);
	if (get_token(*next_tokens)->type == TERMINATOR)
		return (NG);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG);
	return (OK);
}

int	grammar_re_output(t_list **next_tokens, int subshell_count)
{
	(void)subshell_count;
	if (is_in(NG_NEXT_TO_R_OUTPUT, get_token(*next_tokens)))
		return (NG);
	if (get_token(*next_tokens)->type == TERMINATOR)
		return (NG);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG);
	return (OK);
}
