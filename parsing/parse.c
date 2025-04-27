/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 20:10:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

void	free_abs_node(void *target)
{
	t_abs_node	*abs_node;

	abs_node = (t_abs_node *)target;
	if (abs_node)
	{
		free(abs_node->cmd_args);
		free(abs_node->expanded_args);
		free(abs_node->token);
		free(abs_node);
	}
}

int	parse(t_list *token_list, t_list **abs_tree)
{
	if (token_list == NULL)
		return (EXIT_S_FAILURE);
	if (check_tokens_grammar(token_list) == NG)
		return (EXIT_S_SYNTAX_ERROR);
	*abs_tree = ft_lstnew(NULL);
	if (abs_tree == NULL)
		return (EXIT_S_FAILURE);
	return (EXIT_S_SUCCESS);
}
