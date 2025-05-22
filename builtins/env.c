/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:19 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/23 01:39:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	ft_env(t_list *env_list)
{
	t_env_var	*env;

	while (env_list)
	{
		env = (t_env_var *)env_list->content;
		if (env->value)
			printf("%s=%s\n", env->name, env->value);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}
