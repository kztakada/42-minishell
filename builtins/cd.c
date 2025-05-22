/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:52:52 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/20 01:52:46 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static void	update_oldpwd_env(t_list *env_lst)
{
	if (is_alredy_exist(env_lst, "OLDPWD"))
		update_env_value(&env_lst, "OLDPWD", getenv("PWD"));
	else
		create_add_new_env(&env_lst, "OLDPWD", getenv("PWD"));
	return ;
}

static void	update_pwd_env(t_list *env_lst)
{
	if (is_alredy_exist(env_lst, "PWD"))
		update_env_value(&env_lst, "PWD", getcwd(NULL, 0));
	else
		create_add_new_env(&env_lst, "PWD", getcwd(NULL, 0));
	return ;
}

static int	ft_cd_home(t_list *env_list)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (cd_err_msg_home());
	if (!chdir(home))
		return (cd_err_msg_file(home));
	update_oldpwd_env(env_list);
	update_pwd_env(env_list);
	return (EXIT_SUCCESS);
}

int	ft_cd(char *path, t_list *env_list)
{
	if (!path)
		return (ft_cd_home(env_list));
	if (chdir(path) == -1)
		return (cd_err_msg_file(path));
	update_oldpwd_env(env_list);
	update_pwd_env(env_list);
	return (EXIT_SUCCESS);
}
