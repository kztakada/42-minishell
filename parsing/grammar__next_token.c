/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__next_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:51:38 by katakada          #+#    #+#             */
/*   Updated: 2025/05/16 11:53:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static int	grammar_operator(t_token *test_token, t_list **next_tokens,
		int subshell_depth)
{
	t_gram_operator	*g_operator;

	g_operator = (t_gram_operator[]){
		grammar_binop_and,
		grammar_binop_or,
		grammar_pipe,
		grammar_quote_single,
		grammar_quote_double,
	};
	return (g_operator[gf(test_token, G_OPERATORS)](next_tokens,
		subshell_depth));
}

static int	grammar_redirection(t_token *test_token, t_list **next_tokens,
		int subshell_depth, t_bool *strict_mode)
{
	t_gram_redirection	*g_redirection;

	g_redirection = (t_gram_redirection[]){
		grammar_heredoc,
		grammar_re_append,
		grammar_re_input,
		grammar_re_output,
	};
	return (g_redirection[gf(test_token, REDIRECT_OP)](next_tokens, subshell_depth,
		strict_mode));
}

static int	grammar_subshell(t_token *test_token, t_list **next_tokens,
		int *subshell_depth)
{
	t_gram_shell_term	*g_subshell;

	g_subshell = (t_gram_shell_term[]){grammar_sub_open, grammar_sub_close};
	return (g_subshell[gf(test_token, SUBSHELL_OP)](next_tokens,
		subshell_depth));
}

int	grammar_next_token(t_token *test_token, t_list **next_tokens,
		int *subshell_depth, t_bool *strict_mode)
{
	if (is_in(SUBSHELL_OP, test_token))
		return (grammar_subshell(test_token, next_tokens, subshell_depth));
	else if (is_in(G_OPERATORS, test_token))
		return (grammar_operator(test_token, next_tokens, *subshell_depth));
	else if (is_in(REDIRECT_OP, test_token))
		return (grammar_redirection(test_token, next_tokens, *subshell_depth,
				strict_mode));
	else
		return (grammar_operand_text(test_token, next_tokens, *subshell_depth,
				strict_mode));
}
