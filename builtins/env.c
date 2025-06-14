/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:19 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/14 18:20:17 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "exec.h"

static t_bool	put_resolved_path(char *name, char *value, t_list *env_vars)
{
	char	*resolved;
	t_path	path;

	if (!name || !value || env_vars == NULL)
		return (FALSE);
	if (ft_strcmp(name, "_") != 0)
		return (FALSE);
	if (is_builtin(value))
		resolved = ft_strjoin("./minishell/", value);
	else
	{
		path = get_path(value, env_vars);
		if (path.err.exit_s != EXIT_S_SUCCESS)
			return (FALSE);
		resolved = ft_strdup(path.path);
	}
	if (!resolved)
		return (FALSE);
	ft_putstr_fd(resolved, STDOUT_FILENO);
	free(resolved);
	return (TRUE);
}

int	ft_env(t_list *env_list)
{
	t_env_var	*env;

	if (!is_env_exist(env_list, "PATH"))
		return (env_err_msg_path_env());
	while (env_list)
	{
		env = (t_env_var *)env_list->content;
		if (env->value)
		{
			ft_putstr_fd(env->name, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			if (!put_resolved_path(env->name, env->value, env_list))
				ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		env_list = env_list->next;
	}
	return (EXIT_S_SUCCESS);
}
