/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:08 by katakada          #+#    #+#             */
/*   Updated: 2025/05/23 02:26:35 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_abs_node *abs_tree, t_env *env)
{
	t_exit_status	result;
	t_std			std;

	result = expander(abs_tree, *env);
	if (result != 0)
	{
		*(env->exit_status) = result;
		return ;
	}
	dup2(std.saved_stdin, 0);
	dup2(std.saved_stdout, 1);
	result = exec_cmd(abs_tree, env, std);
	*(env->exit_status) = result;
	return ;
}
