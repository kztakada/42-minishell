/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_builtin_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:10:44 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 00:10:11 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "exec.h"

// env
int	env_err_msg_path_env(void)
{
	ft_putstr_fd("minishell: env: ", STDERR_FILENO);
	ft_putendl_fd("No such file or directory", STDERR_FILENO);
	return (EXIT_S_CMD_NOT_FOUND);
}

// cd
int	cd_err_msg_file(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}

int	cd_err_msg_permission(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": Permission denied", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}

int	cd_err_msg_home(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}

int	cd_err_msg_args(void)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}
