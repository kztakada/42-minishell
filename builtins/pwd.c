/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:41 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/17 18:23:06 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", path);
	return (EXIT_SUCCESS);
}
