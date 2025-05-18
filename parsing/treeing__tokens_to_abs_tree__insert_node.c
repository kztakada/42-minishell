/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__tokens_to_abs_tree__insert_node.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:08:34 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:28:02 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_binary_result	insert_binary_node_to_abs_tree(t_list *tokens_begin,
		t_abs_node **abs_tree, t_parsing_state *parsing_state)
{
	t_abs_node	*new_node;

	// 新規ノード作成
	if (get_token(tokens_begin)->type == OP_AND)
		new_node = init_abs_node(ABS_BIN_AND);
	else
		new_node = init_abs_node(ABS_BIN_OR);
	if (new_node == NULL)
		return (FAILURE_BIN_R);
	// 条件分岐
	new_node->left = get_tree_top_node(parsing_state);
	parsing_state->working_node = &(new_node->right);
	parsing_state->working_node_pos = B_OP_RIGHT;
	// サブシェルかどうかで分岐
	if (abs_tree && abs_tree == parsing_state->tree_top_node)
		*abs_tree = new_node;
	*(parsing_state->tree_top_node) = new_node;
	return (SUCCESS_BIN_R);
}

static t_bool	is_subshell_node_state(t_parsing_state *parsing_state)
{
	if (get_tree_top_node(parsing_state) != NULL
		&& get_tree_top_node(parsing_state)->is_subshell == TRUE)
		return (TRUE);
	return (FALSE);
}

static t_bool	is_pipe_node_state(t_parsing_state *parsing_state)
{
	if (get_tree_top_node(parsing_state) != NULL
		&& parsing_state->working_node_pos == PIPE_RIGHT)
		return (TRUE);
	return (FALSE);
}

t_binary_result	insert_pipe_node_to_abs_tree(t_abs_node **abs_tree,
		t_parsing_state *parsing_state)
{
	t_abs_node	*new_node;

	new_node = init_abs_node(ABS_PIPE);
	if (new_node == NULL)
		return (FAILURE_BIN_R);
	if (is_subshell_node_state(parsing_state) == TRUE
		|| is_pipe_node_state(parsing_state) == TRUE)
	{
		new_node->left = get_tree_top_node(parsing_state);
		parsing_state->working_node = &(new_node->right);
		parsing_state->working_node_pos = PIPE_RIGHT;
		if (abs_tree && abs_tree == parsing_state->tree_top_node)
			*abs_tree = new_node;
		*(parsing_state->tree_top_node) = new_node;
	}
	else
	{
		new_node->left = get_working_node(parsing_state);
		*(parsing_state->working_node) = new_node;
		parsing_state->working_node = &(new_node->right);
		parsing_state->working_node_pos = PIPE_RIGHT;
		if (abs_tree && abs_tree == parsing_state->working_node)
			*abs_tree = new_node;
	}
	return (SUCCESS_BIN_R);
}
