/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env__utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:20:37 by katakada          #+#    #+#             */
/*   Updated: 2025/06/04 15:54:31 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_var(void *env_var)
{
	t_env_var	*to_free_object;

	to_free_object = (t_env_var *)env_var;
	if (to_free_object)
	{
		if (to_free_object->name)
			free(to_free_object->name);
		if (to_free_object->value)
			free(to_free_object->value);
		free(to_free_object);
	}
}

t_env_var	*copy_deep_env_var(t_env_var *env_var)
{
	t_env_var	*new_env_var;

	if (!env_var)
		return (NULL);
	new_env_var = malloc(sizeof(t_env_var));
	if (!new_env_var)
		return (NULL);
	new_env_var->name = ft_strdup(env_var->name);
	if (!new_env_var->name)
		return (free(new_env_var), NULL);
	if (env_var->value)
	{
		new_env_var->value = ft_strdup(env_var->value);
		if (!new_env_var->value)
			return (free(new_env_var->name), free(new_env_var), NULL);
	}
	else
		new_env_var->value = NULL;
	return (new_env_var);
}
