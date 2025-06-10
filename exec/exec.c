/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:08 by katakada          #+#    #+#             */
/*   Updated: 2025/06/10 15:21:10 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_saved_std	save_std(void)
{
	t_saved_std	std;

	std.saved_stdin = dup(STDIN_FILENO);
	std.saved_stdout = dup(STDOUT_FILENO);
	return (std);
}

void	exec(t_env *env)
{
	t_exit_status	result;
	t_saved_std		std;

	result = expander(env->abs_tree, *env);
	if (result != 0)
	{
		*(env->exit_status) = result;
		return ;
	}
	std = save_std();
	result = exec_abs(env->abs_tree, env, &std, FALSE);
	*(env->exit_status) = result;
	return ;
}
