/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:08 by katakada          #+#    #+#             */
/*   Updated: 2025/06/09 18:43:03 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "for_test_print.h"

void	exec(t_abs_node *abs_tree, t_env *env)
{
	t_exit_status	result;
	t_saved_std		std;

	result = expander(abs_tree, *env);
	if (result != 0)
	{
		*(env->exit_status) = result;
		return ;
	}
	std = save_stds();
	print_abs_tree(abs_tree);
	result = exec_abs(abs_tree, env, &std, FALSE);
	*(env->exit_status) = result;
	return ;
}
