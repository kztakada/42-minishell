/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:41 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 13:07:36 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_pwd(t_list *env_list)
{
	char	*path;

	path = ft_strdup(get_env_value(env_list, "PWD"));
	if (!path)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (perror(ERROR_GETCWD), EXIT_S_FAILURE);
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(path);
	return (EXIT_S_SUCCESS);
}
