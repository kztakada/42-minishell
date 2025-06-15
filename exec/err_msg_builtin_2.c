/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_builtin_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:37:49 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 07:46:59 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

// cd
int	cd_err_msg_no_file(char *path)
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

int	cd_err_msg_is_file(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putendl_fd(": Not a directory", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}