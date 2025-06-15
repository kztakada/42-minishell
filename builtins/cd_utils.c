/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 07:36:26 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 16:28:27 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	is_path_file(char *path)
{
	struct stat	buf;

	stat(path, &buf);
	if (S_ISREG(buf.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

int	ft_cd_parent(t_list *env_list, t_bool *unset_oldpwd)
{
	char	*parent;
	char	*tmp;
	int		exit_status;

	parent = getcwd(NULL, 0);
	tmp = ft_strrchr(parent, '/');
	if (tmp != NULL)
		*tmp = '\0';
	if (!parent)
		return (perror(ERROR_GETCWD), EXIT_S_FAILURE);
	if (access(parent, F_OK) == -1)
		return (cd_err_msg_no_file(parent));
	if (is_path_file(parent))
		return (cd_err_msg_is_file(parent));
	if (access(parent, X_OK) == -1)
		return (cd_err_msg_permission(".."));
	exit_status = exec_cd(parent, env_list, unset_oldpwd);
	free(parent);
	return (exit_status);
}

static int	msg_not_exist_current_dir(void)
{
	ft_putstr_fd("cd: error retrieving current directory", STDOUT_FILENO);
	ft_putstr_fd(": getcwd: cannot access parent directories", STDOUT_FILENO);
	ft_putendl_fd(": No such file or directory", STDOUT_FILENO);
	return (EXIT_S_SUCCESS);
}

int	access_check(char *path)
{
	if (access(path, F_OK) == -1)
		return (cd_err_msg_no_file(path));
	if (is_path_file(path))
		return (cd_err_msg_is_file(path));
	if (access(path, X_OK) == -1)
		return (cd_err_msg_permission(path));
	else
		return (EXIT_S_SUCCESS);
}

int	exec_cd(char *path, t_list *env_list, t_bool *unset_oldpwd)
{
	int		exit_status;
	char	*env_value;

	if (chdir(path) == -1)
		return (perror(ERROR_CHDIR), EXIT_S_FAILURE);
	exit_status = update_oldpwd_env(env_list, unset_oldpwd);
	if (exit_status != EXIT_S_SUCCESS)
		return (exit_status);
	if (!ft_strcmp(path, ".") && !getcwd(NULL, 0))
	{
		env_value = ft_strjoin(get_env_value(env_list, "PWD"), "/.");
		if (!env_value)
			return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
		update_env_value(&env_list, "PWD", env_value);
		exit_status = msg_not_exist_current_dir();
		free(env_value);
	}
	else
		exit_status = update_pwd_env(env_list);
	return (exit_status);
}
