/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:25:45 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	flush_config(t_bool *strict_mode)
{
	if (strict_mode != NULL)
		*strict_mode = FALSE;
}

static t_list	**setup_check_config(t_token *test_token,
		t_list **current_tokens, t_bool *strict_mode)
{
	t_token	*next_to_test_token;
	t_list	**next_tokens;

	if (*strict_mode == TRUE && test_token->type == OPERAND_TEXT)
		next_tokens = current_tokens;
	else
		next_tokens = forward_token_list(current_tokens);
	next_to_test_token = get_token(*next_tokens);
	if (test_token->type == OP_CLOSE && is_in(REDIRECT_OP, next_to_test_token))
		*strict_mode = TRUE;
	return (next_tokens);
}

// strict_mode:
// bash only strictly checks the second argument
// if the subshell is followed by a redirect.
static int	check_atomic_token_grammar(t_list **current_tokens,
		int *subshell_depth)
{
	static t_bool	strict_mode = FALSE;
	t_token			*test_token;
	t_list			**next_tokens;

	if (current_tokens == NULL || *current_tokens == NULL)
		return (flush_config(&strict_mode), NG_G);
	if (grammar_prefix(get_token(*current_tokens), *subshell_depth) == NG_G)
		return (flush_config(&strict_mode), NG_G);
	test_token = get_token(*current_tokens);
	next_tokens = setup_check_config(test_token, current_tokens, &strict_mode);
	if (grammar_next_token(test_token, next_tokens, subshell_depth,
			&strict_mode) == NG_G)
		return (flush_config(&strict_mode), NG_G);
	if (get_token(*next_tokens)->type == TERMINATOR)
	{
		flush_config(&strict_mode);
		return (grammar_terminator(next_tokens, subshell_depth));
	}
	return (OK_G);
}

static t_loop_status	can_keep_phrasing_tokens(t_token *phrase_top_token,
		t_token *next_token)
{
	if (next_token->type == TERMINATOR)
		return (STOP);
	if (is_in(CMD_MEMBER_OP, phrase_top_token)
		|| phrase_top_token->type == OPERAND_TEXT)
	{
		if (is_in(NOT_CMD_MEMBER_OP, next_token))
			return (STOP);
	}
	else
		return (STOP);
	return (CONTINUE);
}

// "phrase" is the smallest unit of an abstract syntax tree
int	check_one_phrase_grammar(t_list **current_tokens, int *subshell_depth)
{
	t_grammar	g_result;
	t_token		*phrase_top_token;

	phrase_top_token = get_token(*current_tokens);
	g_result = check_atomic_token_grammar(current_tokens, subshell_depth);
	if (g_result == NG_G)
		return (NG_G);
	while (can_keep_phrasing_tokens(phrase_top_token,
			get_token(*current_tokens)) == CONTINUE)
	{
		g_result = check_atomic_token_grammar(current_tokens, subshell_depth);
		if (g_result == NG_G)
			return (NG_G);
	}
	return (g_result);
}
