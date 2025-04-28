/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__follower.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:29:36 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 15:43:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static int	grammar_operator(t_token *test_token, t_list **follower_list)
{
	t_gram_operator	*gc_operator;

	gc_operator = (t_gram_operator[]){
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
	return (gc_operator[gf(test_token, G_OPERATORS)](follower_list));
}

static int	grammar_subshell(t_token *test_token, t_list **follower_list,
		int *subshell_count)
{
	t_gram_shell_term	*gc_subshell;

	gc_subshell = (t_gram_shell_term[]){grammar_sub_open, grammar_sub_close};
	return (gc_subshell[gf(test_token, SUBSHELL_OP)](follower_list,
			subshell_count));
}

int	grammar_follower(t_token *test_token, t_list **follower_list,
		int *subshell_count)
{
	if (is_in(test_token, SUBSHELL_OP))
		return (grammar_subshell(test_token, follower_list, subshell_count));
	else if (is_in(test_token, G_OPERATORS))
		return (grammar_operator(test_token, follower_list));
	else
		return (grammar_operand_text(test_token, follower_list));
}
