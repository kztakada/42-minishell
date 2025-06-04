/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:15 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/03 19:19:48 by kharuya          ###   ########.fr       */
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
		ft_putstr_fd(args[i++], 1);
		if (args[i] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (EXIT_S_SUCCESS);
}
