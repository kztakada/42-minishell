/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__tokens_to_abs_tree__utils.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:27:24 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:28:06 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_abs_node	*get_working_node(t_parsing_state *parsing_state)
{
	if (parsing_state->working_node == NULL)
		return (NULL);
	return (*(parsing_state->working_node));
}

t_abs_node	*get_tree_top_node(t_parsing_state *parsing_state)
{
	if (parsing_state->tree_top_node == NULL)
		return (NULL);
	return (*(parsing_state->tree_top_node));
}

t_bool	is_command_abs_node_content(t_list *tokens)
{
	if (is_in(CMD_MEMBER_OP, get_token(tokens))
		|| get_token(tokens)->type == OPERAND_TEXT)
		return (TRUE);
	return (FALSE);
}

t_bool	is_pipe(t_list *tokens)
{
	if (get_token(tokens)->type == OP_PIPE)
		return (TRUE);
	return (FALSE);
}
