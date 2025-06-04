/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_builtin_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 05:37:49 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/03 19:25:33 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

// exit
int	exit_err_msg_digit(char *arg)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return (EXIT_S_OUT_OF_RANGE);
}

int	exit_err_msg_format(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("bash: exit: too many arguments", 2);
	return (EXIT_S_FAILURE);
}

// export
int	export_err_msg(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (EXIT_S_FAILURE);
}

// unset
int	unset_err_msg(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (EXIT_S_FAILURE);
}
