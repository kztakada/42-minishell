/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:20:54 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 22:44:53 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	check_following_redirect(t_token *testing_token)
{
	if (testing_token->type == OP_HEREDOC)
		return (check_following_re_heredoc(testing_token));
	else if (testing_token->type == OP_APPEND)
		return (check_following_re_append(testing_token));
	else if (testing_token->type == OP_INPUT)
		return (check_following_re_input(testing_token));
	else if (testing_token->type == OP_OUTPUT)
		return (check_following_re_output(testing_token));
	return (perror("Entering unexpected text"), NG);
}

int	check_following_subshell(t_token *testing_token)
{
	if (testing_token->type == OP_OPEN)
		return (check_following_sub_open(testing_token));
	else if (testing_token->type == OP_CLOSE)
		return (check_following_sub_close(testing_token));
	return (perror("Entering unexpected text"), NG);
}

int	check_following_binop_pipe(t_token *testing_token)
{
	if (testing_token->type == OP_AND)
		return (check_following_binop_and(testing_token));
	else if (testing_token->type == OP_OR)
		return (check_following_binop_or(testing_token));
	else if (testing_token->type == OP_PIPE)
		return (check_following_pipe(testing_token));
	return (perror("Entering unexpected text"), NG);
}

int	check_following_text(t_token *testing_token)
{
	if (testing_token->type == QUOTE_SINGLE)
		return (check_following_quote_single(testing_token));
	else if (testing_token->type == QUOTE_DOUBLE)
		return (check_following_quote_double(testing_token));
	else if (testing_token->type == OPERAND_TEXT)
		return (check_following_operand_text(testing_token));
	else if (testing_token->type == TERMINATOR)
		return (check_following_terminator(testing_token));
	return (perror("Entering unexpected text"), NG);
}