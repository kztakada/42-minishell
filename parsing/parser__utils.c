/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:25:06 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 20:16:53 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	free_abs_node(t_abs_node *abs_node)
{
	int	i;

	if (abs_node)
	{
		ft_lstclear(&abs_node->cmd_words, free_parsed_word);
		free_str_list(abs_node->expanded_args);
		ft_lstclear(&abs_node->redirections, free_redirection);
		if (abs_node->expanded_args != NULL)
		{
			i = 0;
			while (abs_node->expanded_args[i] != NULL)
			{
				free(abs_node->expanded_args[i]);
				i++;
			}
		}
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
