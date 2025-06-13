/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:15 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/14 02:01:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

t_bool	is_n_option(char *arg)
{
	int	i;

	if (!arg || ft_strlen(arg) < 2 || arg[0] != '-')
		return (FALSE);
	if (ft_strncmp(arg, "-n", 2) != 0)
		return (FALSE);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_echo(char **args)
{
	int		i;
	t_bool	n_flag;

	i = 1;
	n_flag = FALSE;
	while (args[i] != NULL && is_n_option(args[i]))
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
