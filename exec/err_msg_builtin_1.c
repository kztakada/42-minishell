/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_builtin_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:10:44 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 07:44:44 by kharuya          ###   ########.fr       */
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

// exit
int	exit_err_msg_digit(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	return (EXIT_S_SYNTAX_ERROR);
}

int	exit_err_msg_format(void)
{
	ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}

// export
int	export_err_msg(char *arg)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}

// unset
int	unset_err_msg(char *arg)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
	return (EXIT_S_FAILURE);
}
