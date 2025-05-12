/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__tokens_to_abs_tree.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:24:21 by katakada          #+#    #+#             */
/*   Updated: 2025/05/12 20:39:52 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_abs_node	*init_abs_node(t_abs_node_type abs_node_type)
{
	t_abs_node	*abs_node;

	abs_node = (t_abs_node *)malloc(sizeof(t_abs_node));
	if (abs_node == NULL)
		return (NULL);
	abs_node->is_subshell = FALSE;
	abs_node->type = abs_node_type;
	abs_node->command_args = NULL;
	abs_node->expanded_args = NULL;
	abs_node->redirection_list = NULL;
	abs_node->left = NULL;
	abs_node->right = NULL;
	return (abs_node);
}

static t_bool	is_command_abs_node_content(t_list *tokens)
{
	if (is_in(CMD_MEMBER_OP, get_token(tokens))
		|| get_token(tokens)->type == OPERAND_TEXT)
		return (TRUE);
	return (FALSE);
}

static t_bool	is_pipe(t_list *tokens)
{
	if (get_token(tokens)->type == OP_PIPE)
		return (TRUE);
	return (FALSE);
}

static void	init_parsing_state_only_1st_time(t_abs_node **abs_tree,
		t_parsing_state *parsing_state)
{
	if (*abs_tree == NULL)
	{
		*abs_tree = init_abs_node(COMMAND);
		if (parsing_state != NULL)
		{
			parsing_state->tree_top_node = abs_tree;
			parsing_state->working_node = abs_tree;
			parsing_state->working_node_pos = LEFT;
		}
	}
}

t_binary_result	tokens_to_abs_tree(t_list *tokens_begin, t_list *tokens_end,
		t_abs_node **abs_tree, t_parsing_state *parsing_state)
{
	if (get_token(tokens_begin)->type == TERMINATOR)
		return (SUCCESS_BIN_R);
	init_parsing_state_only_1st_time(abs_tree, parsing_state);
	if (is_command_abs_node_content(tokens_begin))
		return (add_command_to_working_abs_node(tokens_begin, tokens_end,
				parsing_state));
	else if (is_in(BIN_OP, get_token(tokens_begin)))
		return (insert_binary_node_to_abs_tree(tokens_begin, abs_tree,
				parsing_state));
	else if (is_pipe(tokens_begin))
		return (insert_pipe_node_to_abs_tree(abs_tree, parsing_state));
	// else if (is_in(SUBSHELL_OP, get_token(tokens_begin)))
	// 	return (insert_subshell_node_to_abs_tree(tokens_begin, abs_tree,
	// 			parsing_state));
	// else
	// 	return (FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}
