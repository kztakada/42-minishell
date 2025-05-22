/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:17:57 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/22 03:57:33 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static void	reset_stds(t_std std)
{
	dup2(std.saved_stdin, 0);
	dup2(std.saved_stdout, 1);
	return ;
}

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

int	exec_cmd(t_abs_node *abs, t_env *env, t_std std)
{
	int	status;

	if (!abs->expanded_args)
	{
		status = exec_redirection(abs);
		return (reset_stds(std), status);
	}
	if (is_builtin(abs->expanded_args[0]))
	{
		status = exec_redirection(abs);
		if (status != EXIT_S_SUCCESS)
			return (status);
		status = exec_cmd_external(abs, env->envp);
		return (reset_stds(std), status);
	}
	else
		return (exec_cmd_external(abs, env->envp));
}
