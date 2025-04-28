/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 15:30:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"



int	check_tokens_grammar(t_list **token_list, int *subshell_count)
{
	t_token	*testing_token;

	if (token_list == NULL || *token_list == NULL)
		return (NG);
	if (grammar_prefix(get_token(*token_list)) == NG)
		// TODO: idが０番の時だけ処理させる
		return (NG);
	while (*token_list)
	{
		testing_token = get_token(*token_list);
		if (testing_token->type == TERMINATOR)
			break ;
		forward_token_list(token_list);
		if (grammar_follower(testing_token, token_list, subshell_count) == NG)
			return (NG);
	};
	return (grammar_terminator(token_list, subshell_count));
}
