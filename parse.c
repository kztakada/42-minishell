/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/04/05 18:11:45 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_node	*parse(t_token *tokens, t_parse_error *error)
{
	t_node	*as_tree;

	error->code = PARSE_NO_ERROR;
	as_tree = malloc(sizeof(t_node));
	if (as_tree == NULL)
	{
		printf("Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	as_tree->type = N_CMD;
	as_tree->args = tokens->str;
	as_tree->left = NULL;
	as_tree->right = NULL;
	return (as_tree);
}
