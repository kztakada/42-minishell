/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:57:12 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 23:20:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_print.h"

static t_binary_result	expand_abs_tree(t_abs_node *abs_tree, t_env env)
{
	t_binary_result	e_result;

	if (abs_tree == NULL)
		return (SUCCESS_BIN_R);
	e_result = expand_abs_node(abs_tree, env);
	if (e_result == FAILURE_BIN_R)
		return (FAILURE_BIN_R);
	if (abs_tree->left != NULL)
	{
		e_result = expand_abs_tree(abs_tree->left, env);
		if (e_result == FAILURE_BIN_R)
			return (FAILURE_BIN_R);
	}
	if (abs_tree->right != NULL)
	{
		e_result = expand_abs_tree(abs_tree->right, env);
		if (e_result == FAILURE_BIN_R)
			return (FAILURE_BIN_R);
	}
	return (SUCCESS_BIN_R);
}

t_exit_status	expander(t_abs_node *abs_tree, t_env env)
{
	t_binary_result	e_result;

	if (abs_tree == NULL)
		return (EXIT_S_SUCCESS);
	e_result = expand_abs_tree(abs_tree, env);
	if (e_result == FAILURE_BIN_R)
		return (EXIT_S_FAILURE);
	return (EXIT_S_SUCCESS);
}
