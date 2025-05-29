/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:19 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/28 17:16:31 by kharuya          ###   ########.fr       */
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
