/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:56:32 by katakada          #+#    #+#             */
/*   Updated: 2025/06/14 03:17:08 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

t_bool	is_valid_env_name(char *name, t_bool is_interactive)
{
	if (is_interactive)
		return (ft_strcmp(name, "_") != 0);
	return (TRUE);
}

void	put_export_declare(char *name)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(name, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
}

void	put_export_escape_value(char value_c)
{
	ft_putstr_fd("\\", STDOUT_FILENO);
	ft_putchar_fd(value_c, STDOUT_FILENO);
}

void	put_export_declare_null(char *name)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(name, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}
