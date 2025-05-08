/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 22:13:34 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_exit_status	proc_persing(t_list *input_tokens, t_list **next_tokens,
		t_abs_node **abs_tree, t_parse_log *parse_log)
{
	t_grammar	g_result;

	g_result = check_tokens_grammar(next_tokens, &(parse_log->subshell_depth));
	if (g_result == NG_G)
	{
		put_syntax_err(*next_tokens);
		parse_log->subshell_depth = 0;
		return (EXIT_S_SYNTAX_ERROR);
	}
	return (parse_token(input_tokens, *next_tokens, abs_tree, parse_log));
}

t_exit_status	parse_subshell_input(t_list **input_tokens,
		t_abs_node **abs_tree, t_parse_log *parse_log)
{
	t_list			*next_tokens;
	t_exit_status	p_result;

	p_result = EXIT_S_SUCCESS;
	next_tokens = *input_tokens;
	while (get_token(*input_tokens)->type != OP_CLOSE
		&& p_result == EXIT_S_SUCCESS)
	{
		if (get_token(*input_tokens)->type == TERMINATOR)
			return (EXIT_S_SYNTAX_ERROR);
		p_result = proc_persing(*input_tokens, &next_tokens, abs_tree,
				parse_log);
		if (p_result != EXIT_S_SUCCESS)
			return (p_result);
		*input_tokens = next_tokens;
	}
	p_result = proc_persing(*input_tokens, &next_tokens, abs_tree, parse_log);
	if (p_result == EXIT_S_SUCCESS)
		*input_tokens = next_tokens;
	return (p_result);
}

static t_exit_status	parse_input(t_list *input_tokens, t_abs_node **abs_tree,
		t_parse_log *parse_log)
{
	t_list			*next_tokens;
	t_exit_status	p_result;

	p_result = EXIT_S_SUCCESS;
	next_tokens = input_tokens;
	while (get_token(input_tokens)->type != TERMINATOR
		&& p_result == EXIT_S_SUCCESS)
	{
		p_result = proc_persing(input_tokens, &next_tokens, abs_tree,
				parse_log);
		if (p_result == EXIT_S_FAILURE)
			break ;
		if (parse_log->heredoc_list != NULL && parse_log->subshell_depth == 0)
			call_heredoc(parse_log);
		input_tokens = next_tokens;
	}
	if (parse_log->heredoc_list != NULL)
		ft_lstclear(&(parse_log->heredoc_list), no_del);
	return (p_result);
}

t_exit_status	parser(t_list *input_tokens, t_abs_node **abs_tree)
{
	t_parse_log	parse_log;

	if (input_tokens == NULL)
		return (EXIT_S_FAILURE);
	parse_log.subshell_depth = 0;
	parse_log.status = LEFT;
	parse_log.heredoc_list = NULL;
	return (parse_input(input_tokens, abs_tree, &parse_log));
}
