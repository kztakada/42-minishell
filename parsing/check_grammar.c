/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/05/04 23:40:24 by katakada         ###   ########.fr       */
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
	test_token = get_token(*current_tokens);
	forward_token_list(current_tokens);
	if (grammar_next_token(test_token, current_tokens, subshell_count) == NG)
		return (NG);
	if (get_token(*current_tokens)->type == TERMINATOR)
		return (grammar_terminator(current_tokens, subshell_count));
	return (OK);
}
