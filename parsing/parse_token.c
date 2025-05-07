/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 04:36:53 by katakada          #+#    #+#             */
/*   Updated: 2025/05/08 02:30:02 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_abs_node	*init_abs_node(void)
{
	t_abs_node	*abs_node;

	abs_node = (t_abs_node *)malloc(sizeof(t_abs_node));
	if (abs_node == NULL)
		return (NULL);
	abs_node->type = COMMAND;
	abs_node->command_args = NULL;
	abs_node->expanded_args = NULL;
	abs_node->redirection_list = NULL;
	abs_node->left = NULL;
	abs_node->right = NULL;
	return (abs_node);
}

t_exit_status	parse_token(t_list *input_tokens, t_list *next_tokens,
		t_abs_node **abs_tree, t_parse_log *perse_log)
{
	(void)next_tokens;
	*abs_tree = init_abs_node();
	if (abs_tree == NULL)
		return (EXIT_FAILURE);
	if (get_token(input_tokens)->type == OP_HEREDOC)
		return (parse_heredoc(input_tokens, next_tokens, abs_tree, perse_log));
	return (EXIT_S_SUCCESS);
}
