/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:41 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 16:31:58 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static int	pwd_err_msg_pwd(void)
{
	ft_putstr_fd("minishell: pwd: PWD not set\n", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}

int	ft_pwd(t_list *env_list)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		if (is_env_exist(env_list, "PWD"))
		{
			path = ft_strdup(get_env_value(env_list, "PWD"));
			if (!path)
				return (perror(ERROR_GETCWD), EXIT_S_FAILURE);
		}
		else
			return (pwd_err_msg_pwd());
	}
	ft_putstr_fd(path, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(path);
	return (EXIT_S_SUCCESS);
}
