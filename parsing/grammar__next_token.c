/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:51:38 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 18:56:45 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static int	grammar_operator(t_token *test_token, t_list **next_tokens)
{
	t_gram_operator	*g_operator;

	g_operator = (t_gram_operator[]){
		grammar_heredoc,
		grammar_re_append,
		grammar_binop_and,
		grammar_binop_or,
		grammar_pipe,
		grammar_re_input,
		grammar_re_output,
		grammar_quote_single,
		grammar_quote_double,
	};
	return (g_operator[gf(test_token, G_OPERATORS)](next_tokens));
}

static int	grammar_subshell(t_token *test_token, t_list **next_tokens,
		int *subshell_count)
{
	t_gram_shell_term	*g_subshell;

	g_subshell = (t_gram_shell_term[]){
		grammar_sub_open,
		grammar_sub_close
	};
	return (g_subshell[gf(test_token, SUBSHELL_OP)](next_tokens,
		subshell_count));
}

int	grammar_next_token(t_token *test_token, t_list **next_tokens,
		int *subshell_count)
{
	if (is_in(SUBSHELL_OP, test_token))
		return (grammar_subshell(test_token, next_tokens, subshell_count));
	else if (is_in(G_OPERATORS, test_token))
		return (grammar_operator(test_token, next_tokens));
	else
		return (grammar_operand_text(test_token, next_tokens));
}
