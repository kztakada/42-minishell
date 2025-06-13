/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:15 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 21:06:09 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_echo(char **args)
{
	int		i;
	t_bool	n_flag;

	i = 1;
	n_flag = FALSE;
	while (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		n_flag = TRUE;
		i++;
		if (args[i] == NULL)
			return (EXIT_S_SUCCESS);
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i++], STDOUT_FILENO);
		if (args[i] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_S_SUCCESS);
}
