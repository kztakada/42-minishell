/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:51:35 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/06 14:33:01 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static t_path	create_t_path(char *cmd, int err_no, int err_msg, char *err_cause)
{
	t_path	path;

	path.path = cmd;
	path.err.no = err_no;
	path.err.msg = err_msg;
	path.err.cause = err_cause;
	return (path);
}

static t_path	check_exec(char *path, char *cmd)
{
	if ((access(path, X_OK) == 0))
		return (create_t_path(path, ENO_SUCCESS, NONE, NULL));
	else
		return (create_t_path(NULL, ENO_CANT_EXEC, ERRMSG_PERM_DENIED, cmd));
}

static t_path	get_absolute(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (check_exec(cmd, cmd));
	else
		return (create_t_path(NULL, ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd));
}

static t_path	get_relative(char *cmd)
{
	char	**split_path_env;
	char	*tmp_path;
	int		i;

	split_path_env = ft_split(getenv("PATH"), ':');
	i = -1;
	while (split_path_env[++i])
	{
		tmp_path = ft_strjoin_3(split_path_env[i], "/", cmd);
		if (access(tmp_path, F_OK) == 0)
			return (check_exec(tmp_path, cmd));
		free(tmp_path);
	}
	ft_free_char2(split_path_env);
	return (create_t_path(NULL, ENO_NOT_FOUND, ERRMSG_CMD_NOT_FOUND, cmd));
}

t_path	get_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (get_absolute(cmd));
	else
		return (get_relative(cmd));
}
