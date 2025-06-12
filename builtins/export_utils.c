/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:56:32 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 00:07:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	put_export_declare(char *name)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(name, 1);
	ft_putstr_fd("=\"", 1);
}

void	put_export_escape_value(char value_c)
{
	ft_putstr_fd("\\", 1);
	ft_putchar_fd(value_c, 1);
}

void	put_export_declare_null(char *name)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(name, 1);
	ft_putstr_fd("\n", 1);
}
