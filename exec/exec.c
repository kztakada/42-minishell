/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:08 by katakada          #+#    #+#             */
/*   Updated: 2025/05/30 01:23:38 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_saved_std	save_std(void)
{
	t_saved_std	std;

	std.saved_stdin = dup(0);
	std.saved_stdout = dup(1);
	return (std);
}

void	exec(t_abs_node *abs_tree, t_env *env)
{
	t_exit_status	result;
	t_saved_std			std;

	result = expander(abs_tree, *env);
	if (result != 0)
	{
		*(env->exit_status) = result;
		return ;
	}
	std = save_std();
	result = exec_abs(abs_tree, env, std, FALSE);
	*(env->exit_status) = result;
	return ;
}
