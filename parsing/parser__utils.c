/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser__utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 21:25:06 by katakada          #+#    #+#             */
/*   Updated: 2025/05/16 11:53:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static void	free_abs_node(t_abs_node *abs_node)
{
	int	i;

	if (abs_node)
	{
		ft_lstclear(&abs_node->command_args, free_parsed_text);
		ft_lstclear(&abs_node->redirection_list, free_redirection);
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

void	no_del(void *target)
{
	(void)target;
}
