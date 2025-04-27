/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:20:54 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 00:24:49 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	check_following_redirect(t_token *testing_token, t_list **follower_list)
{
	if (testing_token->type == OP_HEREDOC)
		return (check_following_re_heredoc(follower_list));
	else if (testing_token->type == OP_APPEND)
		return (check_following_re_append(follower_list));
	else if (testing_token->type == OP_INPUT)
		return (check_following_re_input(follower_list));
	else if (testing_token->type == OP_OUTPUT)
		return (check_following_re_output(follower_list));
	return (perror("Entering unexpected text"), NG);
}

int	check_following_subshell(t_token *testing_token, t_list **follower_list,
		int *subshell_count)
{
	if (testing_token->type == OP_OPEN)
		return (check_following_sub_open(follower_list, subshell_count));
	else if (testing_token->type == OP_CLOSE)
		return (check_following_sub_close(follower_list, subshell_count));
	else if (testing_token->type == TERMINATOR)
		return (check_following_terminator(follower_list, subshell_count));
	return (perror("Entering unexpected text"), NG);
}

int	check_following_binop_pipe(t_token *testing_token, t_list **follower_list)
{
	if (testing_token->type == OP_AND)
		return (check_following_binop_and(follower_list));
	else if (testing_token->type == OP_OR)
		return (check_following_binop_or(follower_list));
	else if (testing_token->type == OP_PIPE)
		return (check_following_pipe(follower_list));
	return (perror("Entering unexpected text"), NG);
}

int	check_following_text(t_token *testing_token, t_list **follower_list)
{
	if (testing_token->type == QUOTE_SINGLE)
		return (check_following_quote_single(follower_list));
	else if (testing_token->type == QUOTE_DOUBLE)
		return (check_following_quote_double(follower_list));
	else if (testing_token->type == OPERAND_TEXT)
		return (check_following_operand_text(testing_token, follower_list));
	return (perror("Entering unexpected text"), NG);
}
