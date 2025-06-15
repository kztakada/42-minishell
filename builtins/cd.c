/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:52:52 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 14:48:14 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	update_oldpwd_env(t_list *env_list, t_bool *unset_oldpwd)
{
	int	status;

	status = EXIT_S_SUCCESS;
	if (is_env_exist(env_list, "OLDPWD"))
	{
		if (is_env_exist(env_list, "PWD"))
			status = update_env_value(&env_list, "OLDPWD",
					get_env_value(env_list, "PWD"));
		else
			status = update_env_value(&env_list, "OLDPWD", "");
	}
	else
	{
		if (!*unset_oldpwd)
		{
			if (is_env_exist(env_list, "PWD"))
				status = create_add_new_env(&env_list, "OLDPWD",
						get_env_value(env_list, "PWD"));
			else
				status = create_add_new_env(&env_list, "OLDPWD", "");
		}
	}
	return (status);
}

int	update_pwd_env(t_list *env_list)
{
	char	*value;

	if (is_env_exist(env_list, "PWD"))
	{
		value = getcwd(NULL, 0);
		if (!value)
			return (perror(ERROR_GETCWD), EXIT_S_FAILURE);
		update_env_value(&env_list, "PWD", value);
		free(value);
	}
	return (EXIT_S_SUCCESS);
}

static int	ft_cd_home(t_list *env_list, t_bool *unset_oldpwd)
{
	char	*home;
	int		exit_status;

	home = get_env_value(env_list, "HOME");
	if (!home)
		return (cd_err_msg_home());
	if (access(home, F_OK) == -1)
		return (cd_err_msg_no_file(home));
	if (access(home, X_OK) == -1)
		return (cd_err_msg_permission(home));
	if (chdir(home) == -1)
		return (cd_err_msg_no_file(home));
	exit_status = update_oldpwd_env(env_list, unset_oldpwd);
	if (exit_status != EXIT_S_SUCCESS)
		return (exit_status);
	exit_status = update_pwd_env(env_list);
	if (exit_status != EXIT_S_SUCCESS)
		return (exit_status);
	return (EXIT_S_SUCCESS);
}

int	ft_cd(char **args, t_list *env_list, t_bool *unset_oldpwd)
{
	char	*path;

	path = NULL;
	if (args[1] != NULL)
	{
		path = args[1];
		if (args[2] != NULL)
			return (cd_err_msg_args());
	}
	if (!path)
		return (ft_cd_home(env_list, unset_oldpwd));
	return (exec_cd(path, env_list, unset_oldpwd));
}
