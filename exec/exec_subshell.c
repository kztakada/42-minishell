/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 06:14:11 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/08 08:09:26 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_subshell(t_abs_node *abs_tree, t_env *env, t_saved_std *std, t_bool piped)
{
	int	status;

	status = exec_redirection(abs_tree->redirections);
	if (status != EXIT_S_SUCCESS)
		return (status);
	status = exec_abs(abs_tree->left, env, std, piped);
	return (reset_stds(std, piped), status);
}
