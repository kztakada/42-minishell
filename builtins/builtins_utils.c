/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 04:49:33 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/15 07:36:52 by kharuya          ###   ########.fr       */
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
				return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
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
		return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
	new_env->name = ft_strdup(name);
	if (!new_env->name)
		return (perror(ERROR_MALLOC), free_env_var(new_env), EXIT_S_FAILURE);
	if (value)
	{
		new_env->value = ft_strdup(value);
		if (!new_env->value)
			return (perror(ERROR_MALLOC), free_env_var(new_env),
				EXIT_S_FAILURE);
	}
	else
		new_env->value = NULL;
	new_list = (t_list *)malloc(sizeof(t_list) * 1);
	if (!new_env)
		return (perror(ERROR_MALLOC), free_env_var(new_env), EXIT_S_FAILURE);
	new_list->content = new_env;
	new_list->next = NULL;
	ft_lstadd_back(env_list, new_list);
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
	if (!arg || !*arg)
		return (1);
	if (ft_isdigit(*arg))
		return (1);
	if (arg[0] == '=')
		return (1);
	while (*arg != '=' && *arg)
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (1);
		arg++;
	}
	return (0);
}
