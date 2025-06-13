/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:22:32 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 21:02:31 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_err	create_t_err(int err_exit_s, int err_msg, char *err_cause)
{
	t_err	err;

	err.exit_s = err_exit_s;
	err.msg = err_msg;
	err.cause = err_cause;
	return (err);
}

t_path	create_t_path(char *cmd, int err_exit_s, int err_msg, char *err_cause)
{
	t_path	path;

	path.path = cmd;
	path.err = create_t_err(err_exit_s, err_msg, err_cause);
	return (path);
}

int	get_exit_status(int status)
{
	int	sig;

	sig = WTERMSIG(status);
	if (WIFSIGNALED(status))
	{
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit\n", STDERR_FILENO);
		return (128 + WTERMSIG(status));
	}
	return (WEXITSTATUS(status));
}

char	**convert_list_to_envp(t_list *env_vars)
{
	int			lst_size;
	int			i;
	t_env_var	*env;
	char		**envp;

	lst_size = ft_lstsize(env_vars);
	envp = (char **)malloc(sizeof(char *) * (lst_size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (i < lst_size)
	{
		env = (t_env_var *)env_vars->content;
		envp[i] = ft_strjoin_3(env->name, "=", env->value);
		if (!envp[i])
			return (free(envp), NULL);
		env_vars = env_vars->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

char	*get_env_value(t_list *env_vars, char *name)
{
	t_env_var	*env;

	while (env_vars)
	{
		env = env_vars->content;
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env_vars = env_vars->next;
	}
	return (NULL);
}
