/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_builtin_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:37:49 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 21:08:59 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

// exit
int	exit_err_msg_digit(char *arg)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	return (EXIT_S_OUT_OF_RANGE);
}

int	exit_err_msg_format(void)
{
	ft_putendl_fd("exit", STDERR_FILENO);
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
