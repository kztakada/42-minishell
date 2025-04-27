/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 00:37:29 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static int	check_prefix_grammar(t_token *testing_token)
{
	if (can_use_as_first_token(testing_token) == FALSE)
		return (NG);
	return (OK);
}

static int	check_following_grammar(t_token *testing_token,
		t_list **follower_list, int *subshell_count)
{
	if (is_in(testing_token, REDIRECT_OP))
		return (check_following_redirect(testing_token, follower_list));
	else if (is_in(testing_token, SUBSHELL_TERM))
		return (check_following_subshell(testing_token, follower_list,
				subshell_count));
	else if (is_in(testing_token, BINARY_OP_PIPE))
		return (check_following_binop_pipe(testing_token, follower_list));
	else
		return (check_following_text(testing_token, follower_list));
}

int	check_tokens_grammar(t_list **token_list, int *subshell_count)
{
	t_token	*testing_token;

	if (token_list == NULL || *token_list == NULL)
		return (NG);
	if (check_prefix_grammar(get_token(*token_list)) == NG)
		return (NG);
	while (*token_list)
	{
		testing_token = get_token(*token_list);
		if (testing_token->type == TERMINATOR)
			break ;
		forward_token_list(token_list);
		if (check_following_grammar(testing_token, token_list,
				subshell_count) == NG)
			return (NG);
	};
	return (check_following_terminator(token_list, subshell_count));
}
