/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:58:56 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/08 05:53:41 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "exec.h"

int	exec_cmd_builtin(char **args, t_env *env)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args[1], env->env_vars, env->unset_oldpwd));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env->env_vars));
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args, env->env_vars));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args, env->env_vars, env->unset_oldpwd));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, env, *(env->exit_status));
	return (EXIT_S_FAILURE);
}
