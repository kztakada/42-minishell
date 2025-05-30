/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_abs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:40:49 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/29 22:12:16 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_abs(t_abs_node *abs_tree, t_env *env, t_saved_std std, t_bool piped)
{
	int status;

	if (!abs_tree)
		return (EXIT_S_SUCCESS);
	if (abs_tree->type == ABS_PIPE)
		return (exec_pipe(abs_tree, env, std));
	else if(abs_tree->type == ABS_BIN_AND)
	{
		status = exec_abs(abs_tree->left, env, std, FALSE);
		if (status == EXIT_S_SUCCESS)
			return (exec_abs(abs_tree->right, env, std, FALSE));
		return (status);
	}
	else if(abs_tree->type == ABS_BIN_OR)
	{
		status = exec_abs(abs_tree->left, env, std, FALSE);
		if (status == EXIT_S_SUCCESS)
			return (status);
		return (exec_abs(abs_tree->right, env, std, FALSE));
	}
	else
		return (exec_cmd(abs_tree, env, std, piped));
}
