/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:15 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/03 21:53:17 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

int	ft_echo(char **args)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	while (ft_strcmp(args[i], "-n") == 0)
	{
		n_flag = true;
		i++;
		if (args[i] == NULL)
			return (0);
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i] != NULL)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
