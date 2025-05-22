/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:51:35 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/23 01:30:23 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static t_path	check_exec(char *path, char *cmd)
{
	if ((access(path, X_OK) == 0))
		return (create_t_path(path, EXIT_S_SUCCESS, NONE, NULL));
	else
		return (create_t_path(NULL, EXIT_S_CMD_FAILURE,
				ERRMSG_PERM_DENIED, cmd));
}

static t_path	get_absolute(char *cmd)
{
	if (access(cmd, F_OK) == 0)
		return (check_exec(cmd, cmd));
	else
		return (create_t_path(NULL, EXIT_S_CMD_NOT_FOUND,
				ERRMSG_CMD_NOT_FOUND, cmd));
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
	return (create_t_path(NULL, EXIT_S_CMD_NOT_FOUND,
			ERRMSG_CMD_NOT_FOUND, cmd));
}

t_path	get_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (get_absolute(cmd));
	else
		return (get_relative(cmd));
}
