/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:25:06 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 21:46:32 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static void	free_abs_node(t_abs_node *abs_node)
{
	if (abs_node)
	{
		free(abs_node->cmd_args);
		free(abs_node->expanded_args);
		free(abs_node->token);
	}
}

void	free_abs_tree(t_abs_node *abs_tree)
{
	if (abs_tree == NULL)
		return ;
	free_abs_node(abs_tree);
	if (abs_tree->left != NULL)
		free_abs_tree(abs_tree->left);
	if (abs_tree->right != NULL)
		free_abs_tree(abs_tree->right);
	free(abs_tree);
}

void	no_del(void *target)
{
	(void)target;
}
