/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:15 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/24 20:43:23 by katakada         ###   ########.fr       */
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
			return (EXIT_SUCCESS);
	}
	while (args[i] != NULL)
	{
		printf("%s", args[i++]);
		if (args[i] != NULL)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (EXIT_SUCCESS);
}
