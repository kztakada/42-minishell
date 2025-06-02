/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:52:52 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/30 20:02:24 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	update_oldpwd_env(t_list *env_list, t_bool *unset_oldpwd)
{
	if (is_env_exist(env_list, "OLDPWD"))
	{
		if (is_env_exist(env_list, "PWD"))
			update_env_value(&env_list, "OLDPWD", getenv("PWD"));
		else
			update_env_value(&env_list, "OLDPWD", "");
	}
	else
	{
		if (!*unset_oldpwd)
		{
			if (is_env_exist(env_list, "PWD"))
				create_add_new_env(&env_list, "OLDPWD", getenv("PWD"));
			else
				create_add_new_env(&env_list, "OLDPWD", "");
		}
	}
	return (EXIT_S_SUCCESS);
}

static int	update_pwd_env(t_list *env_list)
{
	if (is_env_exist(env_list, "PWD"))
		update_env_value(&env_list, "PWD", getcwd(NULL, 0));
	return (EXIT_S_SUCCESS);
}

static int	ft_cd_home(t_list *env_list, t_bool *unset_oldpwd)
{
	char	*home;

	home = get_env_value(env_list, "HOME");
	if (!home)
		return (cd_err_msg_home());
	chdir(home);
	update_oldpwd_env(env_list, unset_oldpwd);
	update_pwd_env(env_list);
	return (EXIT_SUCCESS);
}

int	ft_cd(char *path, t_list *env_list, t_bool *unset_oldpwd)
{
	if (!path)
		return (ft_cd_home(env_list, unset_oldpwd));
	if (chdir(path) == -1)
		return (cd_err_msg_file(path));
	update_oldpwd_env(env_list, unset_oldpwd);
	update_pwd_env(env_list);
	return (EXIT_SUCCESS);
}
