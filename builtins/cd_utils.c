/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 07:36:26 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 13:27:42 by kharuya          ###   ########.fr       */
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

int	exec_cd(char *path, t_list *env_list, t_bool *unset_oldpwd, char *err_msg)
{
	int	exit_status;

	if (access(path, F_OK) == -1)
		return (cd_err_msg_no_file(path));
	if (is_path_file(path))
		return (cd_err_msg_is_file(path));
	if (access(path, X_OK) == -1)
		return (cd_err_msg_permission(err_msg));
	if (chdir(path) == -1)
		return (cd_err_msg_no_file(err_msg));
	exit_status = update_oldpwd_env(env_list, unset_oldpwd);
	if (exit_status != EXIT_S_SUCCESS)
		return (exit_status);
	exit_status = update_pwd_env(env_list);
	if (exit_status != EXIT_S_SUCCESS)
		return (exit_status);
	return (EXIT_S_SUCCESS);
}
