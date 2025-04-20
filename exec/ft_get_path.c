/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:51:35 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/20 01:14:04 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static t_path	create_t_path(char *cmd)
{
	t_path	path;

	path.path = cmd;
	path.err.no = ENO_SUCCESS;
	path.err.msg = NULL;
	path.err.cause = NULL;
	return (path);
}

static t_path	ft_get_absolute(char *cmd)
{
	t_path	path;
	int		i;
	char	**path_env_split;

	path_env_split = ft_split(getenv("PATH"), ":");
	i = 0;
	while (path_env_split[i])
	{
		if (!access(path_env_split[i], X_OK))
		{
			path = create_t_path(path_env_split[i]);
			free(path_env_split);
			return (path);
		}
		i++;
	}

	free(path_env_split);
}

static t_path	ft_get_relative(char *cmd)
{
	t_path	path;
}

t_path	ft_get_path(char *cmd)
{
	t_path	path;

	if (ft_strchr(cmd, '/'))
		path = ft_get_absolute(cmd);
	else
		path = ft_get_relative(cmd);
	//ここから
	
}
