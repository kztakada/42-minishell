/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:54:38 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/03 21:55:21 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

int	ft_exec_builtin(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args[1]));
	else if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(args));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
}
