/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:49:33 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/04 05:02:16 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

int	update_env_value(t_list **env_list, char *name, char *value)
{
	t_list		*current;
	t_env_var	*env;

	if (value == NULL)
		return (EXIT_S_SUCCESS);
	current = *env_list;
	while (current)
	{
		env = (t_env_var *)current->content;
		if (!ft_strcmp(env->name, name))
		{
			free(env->value);
			env->value = ft_strdup(value);
			if (env->value == NULL)
				return (err_msg_malloc());
			return (EXIT_S_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_S_SUCCESS);
}

int	create_add_new_env(t_list **env_list, char *name, char *value)
{
	t_list		*new_list;
	t_env_var	*new_env;

	new_env = (t_env_var *)malloc(sizeof(t_env_var) * 1);
	if (!new_env)
		return (err_msg_malloc());
	new_env->name = ft_strdup(name);
	if (!new_env->name)
		return (err_msg_malloc());
	if (value)
	{
		new_env->value = ft_strdup(value);
		if (!new_env->value)
			return (err_msg_malloc());
	}
	else
		new_env->value = NULL;
	new_list = (t_list *)malloc(sizeof(t_list) * 1);
	if (!new_env)
		return (err_msg_malloc());
	new_list->content = new_env;
	new_list->next = NULL;
	while ((*env_list)->next)
		(*env_list) = (*env_list)->next;
	(*env_list)->next = new_list;
	return (EXIT_S_SUCCESS);
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

t_env_var	*copy_t_env_var(t_env_var *env)
{
	t_env_var *env_cpy;

	env_cpy = (t_env_var *)malloc(sizeof(t_env_var) * 1);
	if (!env_cpy)
		return (NULL);
	env_cpy->name = ft_strdup(env->name);
	if (!env->name)
		return (NULL);
	if (env->value)
	{
		env_cpy->value = ft_strdup(env->value);
		if (!env_cpy->value)
			return (NULL);
	}
	else
		env_cpy->value = NULL;
	return (env_cpy);
}