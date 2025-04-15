/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:52:52 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/15 02:29:00 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static void	update_oldpwd_env(t_env *env_lst)
{
	if (is_alredy_exist(env_lst, "OLDPWD"))
		update_env_value(&env_lst, "OLDPWD", getenv("PWD"));
	else
		create_new_env(&env_lst, "OLDPWD", getenv("PWD"));
	return ;
}

static void update_pwd_env(t_env *env_lst)
{
	if (is_alredy_exist(env_lst, "PWD"))
		update_env_value(&env_lst, "PWD", getcwd(NULL, 0));
	else
		create_new_env(&env_lst, "PWD", getcwd(NULL, 0));
	return ;
}

static int	cd_err_msg(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (1);
}

static int	ft_cd_home(t_minishell *minishell)
{
	char *home;

	home = getenv("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	chdir(home);
	update_oldpwd_env(minishell->env_lst);
	update_pwd_env(minishell->env_lst);
	return (0);
}

int	ft_cd(char *path, t_minishell *minishell)
{
	if (!path)
		return (ft_cd_home(minishell));
	if (chdir(path) == -1)
		return (cd_err_msg(path));
	update_oldpwd_env(minishell->env_lst);
	update_pwd_env(minishell->env_lst);
	return (0);
}
