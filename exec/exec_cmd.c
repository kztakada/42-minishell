/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:17:57 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/10 01:25:42 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env"))
		return (TRUE);
	return (FALSE);
}

int	exec_cmd(t_abs_node *abs_tree, t_env *env, t_saved_std *std, t_bool redirected)
{
	int	status;

	if (!abs_tree->expanded_args)
	{
		status = exec_redirection(abs_tree->redirections);
		return (reset_stds(std, redirected), status);
	}
	if (is_builtin(abs_tree->expanded_args[0]))
	{
		status = exec_redirection(abs_tree->redirections);
		if (status != EXIT_S_SUCCESS)
			return (status);
		status = exec_cmd_builtin(abs_tree->expanded_args, env);
		return (reset_stds(std, redirected), status);
	}
	else
		return (exec_cmd_external(abs_tree, env->env_vars));
}
