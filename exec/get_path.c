/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:51:35 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/14 23:01:27 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_path	check_exec(char *path, char *cmd)
{
	struct stat	buf;

	stat(path, &buf);
	if (S_ISDIR(buf.st_mode))
		return (create_t_path(cmd, EXIT_S_FAILURE, ERRMSG_IS_DIRECTORY, cmd));
	if ((access(path, X_OK) == 0))
		return (create_t_path(path, EXIT_S_SUCCESS, NONE, NULL));
	else
		return (create_t_path(cmd, EXIT_S_CMD_FAILURE, ERRMSG_PERM_DENIED,
				cmd));
}

static t_path	get_absolute(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (check_exec(cmd, cmd));
	else
		return (create_t_path(cmd, EXIT_S_CMD_NOT_FOUND, ERRMSG_NO_SUCH_FILE,
				cmd));
}

static t_path	get_relative(char *cmd, t_list *env_vars)
{
	char	*path_env_value;
	char	**split_path_env;
	char	*tmp_path;
	int		i;

	path_env_value = get_env_value(env_vars, "PATH");
	split_path_env = ft_split(path_env_value, ':');
	if (!split_path_env)
		return (create_t_path(cmd, EXIT_S_FAILURE, ERRMSG_MALLOC, cmd));
	i = -1;
	while (split_path_env[++i])
	{
		tmp_path = ft_strjoin_3(split_path_env[i], "/", cmd);
		if (!tmp_path)
			return (ft_free_char2(split_path_env), create_t_path(cmd,
					EXIT_S_FAILURE, ERRMSG_MALLOC, cmd));
		if (access(tmp_path, F_OK) == 0)
			return (check_exec(tmp_path, cmd));
		free(tmp_path);
	}
	ft_free_char2(split_path_env);
	return (create_t_path(cmd, EXIT_S_CMD_NOT_FOUND, ERRMSG_CMD_NOT_FOUND,
			cmd));
}

t_path	get_path(char *cmd, t_list *env_vars)
{
	if (ft_strcmp(cmd, "") == 0 && is_env_exist(env_vars, "PATH"))
		return (create_t_path(cmd, EXIT_S_CMD_NOT_FOUND, ERRMSG_CMD_NOT_FOUND,
				cmd));
	if (ft_strcmp(cmd, "") == 0 && !is_env_exist(env_vars, "PATH"))
		return (create_t_path(cmd, EXIT_S_FAILURE, ERRMSG_NO_SUCH_FILE, cmd));
	if (is_env_exist(env_vars, "PATH") || ft_strchr(cmd, '/') != NULL)
	{
		if (ft_strchr(cmd, '/'))
			return (get_absolute(cmd));
		else
			return (get_relative(cmd, env_vars));
	}
	else
		return (create_t_path(cmd, EXIT_S_CMD_NOT_FOUND, ERRMSG_NO_SUCH_FILE,
				cmd));
}
