/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/05/02 00:55:18 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	check_tokens_grammar(t_list **current_tokens, int *subshell_count)
{
	t_token	*test_token;

	if (current_tokens == NULL || *current_tokens == NULL)
		return (NG);
	if (grammar_prefix(get_token(*current_tokens), *subshell_count) == NG)
		return (NG);
	while (*current_tokens)
	{
		test_token = get_token(*current_tokens);
		if (test_token->type == TERMINATOR)
			break ;
		forward_token_list(current_tokens);
		if (grammar_next_token(test_token, current_tokens,
				subshell_count) == NG)
			return (NG);
	}
	return (grammar_terminator(current_tokens, subshell_count));
}
