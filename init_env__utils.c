/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env__utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:20:37 by katakada          #+#    #+#             */
/*   Updated: 2025/05/13 20:21:02 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

void	free_env_var(void *env_var)
{
	t_env_var	*to_free_object;

	to_free_object = (t_env_var *)env_var;
	if (to_free_object)
	{
		free(to_free_object->name);
		free(to_free_object->value);
		free(to_free_object);
	}
}
