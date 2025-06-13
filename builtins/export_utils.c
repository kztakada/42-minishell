/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:56:32 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 21:07:00 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
