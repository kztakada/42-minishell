/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:40:49 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 21:41:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_abs(t_abs_node *abs_tree, t_env *env, t_saved_std *std,
		t_bool redirected)
{
	int	status;

	if (!abs_tree)
		return (*(env->exit_status));
	if (abs_tree->type == ABS_SUBSHELL)
		return (exec_subshell(abs_tree, env, std));
	else if (abs_tree->type == ABS_PIPE)
		return (exec_pipe(abs_tree, env, std));
	else if (abs_tree->type == ABS_BIN_AND)
	{
		status = exec_abs(abs_tree->left, env, std, redirected);
		if (status == EXIT_S_SUCCESS)
			return (exec_abs(abs_tree->right, env, std, redirected));
		return (status);
	}
	else if (abs_tree->type == ABS_BIN_OR)
	{
		status = exec_abs(abs_tree->left, env, std, redirected);
		if (status == EXIT_S_SUCCESS)
			return (status);
		return (exec_abs(abs_tree->right, env, std, redirected));
	}
	else
		return (exec_cmd(abs_tree, env, std, redirected));
}
