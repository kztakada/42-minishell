/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/05/06 00:56:19 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

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
int	check_tokens_grammar(t_list **current_tokens, int *subshell_count)
{
	static t_bool	strict_mode = FALSE;
	t_token			*test_token;
	t_list			**next_tokens;

	if (current_tokens == NULL || *current_tokens == NULL)
		return (flush_config(&strict_mode), NG);
	if (grammar_prefix(get_token(*current_tokens), *subshell_count) == NG)
		return (flush_config(&strict_mode), NG);
	test_token = get_token(*current_tokens);
	next_tokens = setup_check_config(test_token, current_tokens, &strict_mode);
	if (grammar_next_token(test_token, next_tokens, subshell_count,
			&strict_mode) == NG)
		return (flush_config(&strict_mode), NG);
	if (get_token(*next_tokens)->type == TERMINATOR)
	{
		flush_config(&strict_mode);
		return (grammar_terminator(next_tokens, subshell_count));
	}
	return (OK);
}
