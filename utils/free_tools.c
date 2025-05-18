/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:44:11 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 20:17:03 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_list(char **str_list)
{
	int	i;

	if (str_list == NULL)
		return ;
	i = 0;
	while (str_list[i] != NULL)
	{
		free(str_list[i]);
		i++;
	}
	free(str_list);
}

void	no_del(void *target)
{
	(void)target;
}
