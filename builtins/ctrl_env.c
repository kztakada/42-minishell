/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 02:14:28 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/09 14:28:25 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

t_bool	update_env_value(t_env **env_lst, char *key, char *value)
{
	while (ft_strcmp((*env_lst)->key, key))
		(*env_lst) = (*env_lst)->next;
	free((*env_lst)->value);
	(*env_lst)->value = ft_strdup(value);
	if ((*env_lst)->value == NULL)
		return (FALSE);
	return (TRUE);
}

t_bool	create_add_new_env(t_env **env_lst, char *key, char *value)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env) * 1);

	new_env->key = ft_strdup(key);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	while ((*env_lst)->next)
		(*env_lst) = (*env_lst)->next;
	(*env_lst)->next = new_env;
	return (TRUE);
}

int	is_alredy_exist(t_env *env_lst, char *key)
{
	while (env_lst)
	{
		if (!ft_strcmp(env_lst->key, key))
			return (1);
		env_lst = env_lst->next;
	}
	return (0);
}

int	check_key_error(char *arg)
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
