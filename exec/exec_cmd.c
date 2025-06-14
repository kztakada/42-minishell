/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 01:17:57 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/14 18:21:12 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"exit") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (TRUE);
	return (FALSE);
}

static void	set_current_token_env_var(char **args, t_env *env)
{
	char	*value;
	int		i;

	if (!args || !args[0] || !env || env->env_vars == NULL)
		return ;
	if (!(env->is_interactive) && (ft_strcmp(args[0], "export") == 0
			|| ft_strcmp(args[0], "unset") == 0))
		return ;
	i = 0;
	while (args[i])
	{
		value = args[i];
		i++;
	}
	if (!value)
		return ;
	if (is_env_exist(env->env_vars, "_"))
		update_env_value(&(env->env_vars), "_", value);
	else
		create_add_new_env(&(env->env_vars), "_", value);
	return ;
}

int	exec_cmd(t_abs_node *abs_tree, t_env *env, t_saved_std *std,
		t_bool redirected)
{
	int	status;

	if (!abs_tree->expanded_args)
	{
		status = exec_redirection(abs_tree->redirections);
		return (reset_stds(std, redirected), status);
	}
	set_current_token_env_var(abs_tree->expanded_args, env);
	if (is_builtin(abs_tree->expanded_args[0]))
	{
		status = exec_redirection(abs_tree->redirections);
		if (status != EXIT_S_SUCCESS)
			return (status);
		status = exec_cmd_builtin(abs_tree->expanded_args, env);
		return (reset_stds(std, redirected), status);
	}
	else
		return (exec_cmd_external(abs_tree, env->env_vars, env));
}
