/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:14:28 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/30 20:24:54 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

t_bool	update_env_value(t_list **env_list, char *name, char *value)
{
	t_list		*current;
	t_env_var	*env;

	current = *env_list;
	while (current)
	{
		env = (t_env_var *)current->content;
		if (!ft_strcmp(env->name, name))
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (env->value == NULL)
				return (FALSE);
			return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}

t_bool	create_add_new_env(t_list **env_list, char *name, char *value)
{
	t_list		*new_list;
	t_env_var	*new_env;

	new_env = (t_env_var *)malloc(sizeof(t_env_var) * 1);
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_list = (t_list *)malloc(sizeof(t_list) * 1);
	new_list->content = new_env;
	new_list->next = NULL;
	while ((*env_list)->next)
		(*env_list) = (*env_list)->next;
	(*env_list)->next = new_list;
	return (TRUE);
}

int	is_env_exist(t_list *env_list, char *name)
{
	t_env_var	*env;

	while (env_list)
	{
		env = (t_env_var *)env_list->content;
		if (!ft_strcmp(env->name, name))
			return (TRUE);
		env_list = env_list->next;
	}
	return (FALSE);
}

int	check_name_error(char *arg)
{
	if (ft_isdigit(*arg))
		return (1);
	while (*arg != '=' && *arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (1);
		arg++;
	}
	return (0);
}
