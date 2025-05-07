/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:01:34 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 20:31:04 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
#define NG_NEXT_TO_HEREDOC " << >> && || | < > ( ) \n"
#define NG_NEXT_TO_R_INPUT " << >> && || | < > ( ) \n"
#define NG_NEXT_TO_R_OUTPUT " << >> && || | < > ( ) \n"
#define NG_NEXT_TO_R_APPEND " << >> && || | < > ( ) \n"

// " << >> && || | < > ( ) ' \" \n"

int	grammar_heredoc(t_list **next_tokens, int subshell_depth,
		t_bool *strict_mode)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_HEREDOC, get_token(*next_tokens)))
		return (NG_G);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG_G);
	if (*strict_mode == TRUE)
		return (grammar_subshell_to_redirect(next_tokens, strict_mode));
	return (OK_G);
}

int	grammar_re_append(t_list **next_tokens, int subshell_depth,
		t_bool *strict_mode)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_R_APPEND, get_token(*next_tokens)))
		return (NG_G);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG_G);
	if (*strict_mode == TRUE)
		return (grammar_subshell_to_redirect(next_tokens, strict_mode));
	return (OK_G);
}

int	grammar_re_input(t_list **next_tokens, int subshell_depth,
		t_bool *strict_mode)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_R_INPUT, get_token(*next_tokens)))
		return (NG_G);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG_G);
	if (*strict_mode == TRUE)
		return (grammar_subshell_to_redirect(next_tokens, strict_mode));
	return (OK_G);
}

int	grammar_re_output(t_list **next_tokens, int subshell_depth,
		t_bool *strict_mode)
{
	(void)subshell_depth;
	if (is_in(NG_NEXT_TO_R_OUTPUT, get_token(*next_tokens)))
		return (NG_G);
	if (is_in(QUOTE_DICT, get_token(*next_tokens))
		&& get_token((*next_tokens)->next)->type == TERMINATOR)
		return (NG_G);
	if (*strict_mode == TRUE)
		return (grammar_subshell_to_redirect(next_tokens, strict_mode));
	return (OK_G);
}
