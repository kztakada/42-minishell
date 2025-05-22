/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:10:44 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/23 01:40:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"
#include "exec.h"

// cd
int	cd_err_msg_file(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (EXIT_S_FAILURE);
}

int	cd_err_msg_home(void)
{
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (EXIT_S_FAILURE);
}

// exit
void	exit_err_msg_digit(char *arg)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return ;
}

void	exit_err_msg_format(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("bash: exit: too many arguments", 2);
	return ;
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
