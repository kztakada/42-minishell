/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:08 by katakada          #+#    #+#             */
/*   Updated: 2025/05/23 01:10:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec(t_abs_node *abs_tree, t_env *env)
{
	t_exit_status	result;

	result = expander(abs_tree, *env);
	if (result != 0)
	{
		*(env->exit_status) = result;
		return ;
	}
}
