/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__tokens_to_abs_tree.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:24:21 by katakada          #+#    #+#             */
/*   Updated: 2025/06/06 14:49:56 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_binary_result	init_parsing_state_only_1st_time(t_abs_node **abs_tree,
		t_parsing_state *parsing_state)
{
	if (*abs_tree == NULL)
	{
		*abs_tree = init_abs_node(ABS_COMMAND);
		if (*abs_tree == NULL)
			return (FAILURE_BIN_R);
		if (parsing_state != NULL)
		{
			parsing_state->tree_top_node = abs_tree;
			parsing_state->working_node = abs_tree;
			parsing_state->working_node_pos = LEFT;
		}
	}
	return (SUCCESS_BIN_R);
}

t_binary_result	tokens_to_abs_tree(t_list *tokens_begin, t_list *tokens_end,
		t_abs_node **abs_tree, t_parsing_state *parsing_state)
{
	if (get_token(tokens_begin)->type == TERMINATOR)
		return (SUCCESS_BIN_R);
	if (init_parsing_state_only_1st_time(abs_tree,
			parsing_state) == FAILURE_BIN_R)
		return (FAILURE_BIN_R);
	if (is_command_abs_node_content(tokens_begin))
		return (add_command_to_working_abs_node(tokens_begin, tokens_end,
				parsing_state));
	else if (is_in(BIN_OP, get_token(tokens_begin)))
		return (insert_binary_node_to_abs_tree(tokens_begin, abs_tree,
				parsing_state));
	else if (is_pipe(tokens_begin))
		return (insert_pipe_node_to_abs_tree(abs_tree, parsing_state));
	else
		return (FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}

static t_parsing	parse_subshell_input(t_list **input_tokens,
		t_abs_node **abs_tree, t_parsing_state *parsing_state)
{
	t_list		*sequence_end;
	t_parsing	p_result;

	p_result = SUCCESS_P;
	sequence_end = NULL;
	while (get_token(*input_tokens)->type != OP_CLOSE && p_result == SUCCESS_P)
	{
		if (get_token(*input_tokens)->type == TERMINATOR)
			return (SYNTAX_ERROR_P);
		p_result = parse_one_sequence(*input_tokens, &sequence_end, abs_tree,
				parsing_state);
		if (p_result != SUCCESS_P)
			return (p_result);
		*input_tokens = sequence_end;
	}
	p_result = parse_one_sequence(*input_tokens, &sequence_end, abs_tree,
			parsing_state);
	if (p_result == SUCCESS_P)
		*input_tokens = sequence_end;
	return (p_result);
}

t_binary_result	insert_subshell_node_to_abs_tree(t_abs_node **abs_tree,
		t_parsing_state *parsing_state, t_abs_node **first_top_node,
		t_abs_node_type pre_abs_node_type)
{
	t_abs_node	*new_node;

	new_node = init_abs_node(ABS_SUBSHELL);
	if (new_node == NULL)
		return (FAILURE_BIN_R);
	if (pre_abs_node_type == ABS_BIN_AND || pre_abs_node_type == ABS_BIN_OR
		|| pre_abs_node_type == ABS_PIPE)
	{
		new_node->left = get_tree_top_node(parsing_state);
		(*first_top_node)->right = new_node;
		parsing_state->tree_top_node = first_top_node;
		parsing_state->working_node = &(*(parsing_state->tree_top_node))->right;
		parsing_state->working_node_pos = SUBSHELL_TOP;
	}
	else
	{
		parsing_state->tree_top_node = first_top_node;
		new_node->left = get_tree_top_node(parsing_state);
		parsing_state->working_node = parsing_state->tree_top_node;
		parsing_state->working_node_pos = SUBSHELL_TOP;
		if (abs_tree && abs_tree == parsing_state->tree_top_node)
			*abs_tree = new_node;
		*(parsing_state->tree_top_node) = new_node;
	}
	return (SUCCESS_BIN_R);
}

t_parsing	subshell_tokens_to_abs_tree(t_list *tokens_begin,
		t_list **tokens_end, t_abs_node **abs_tree,
		t_parsing_state *parsing_state)
{
	t_abs_node		**first_top_node;
	t_parsing		p_result;
	t_abs_node_type	pre_abs_node_type;

	if (get_token(tokens_begin)->type == OP_CLOSE)
		return (SUCCESS_P);
	if (get_token(tokens_begin)->type != OP_OPEN)
		return (FAILURE_P);
	if (init_parsing_state_only_1st_time(abs_tree,
			parsing_state) == FAILURE_BIN_R)
		return (FAILURE_P);
	first_top_node = parsing_state->tree_top_node;
	pre_abs_node_type = (*first_top_node)->type;
	parsing_state->tree_top_node = parsing_state->working_node;
	p_result = parse_subshell_input(tokens_end, abs_tree, parsing_state);
	if (p_result == SUCCESS_P && get_tree_top_node(parsing_state))
	{
		if (insert_subshell_node_to_abs_tree(abs_tree, parsing_state,
				first_top_node, pre_abs_node_type) == FAILURE_BIN_R)
			return (FAILURE_P);
	}
	return (p_result);
}
