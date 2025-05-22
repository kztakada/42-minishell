/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:43:00 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/20 02:15:14 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static char	*extract_env_var_value(char *env_var_source, int *is_error)
{
	char	*var_value;
	int		var_value_len;
	int		i;

	i = 0;
	var_value = NULL;
	while (env_var_source[i] && env_var_source[i] != '=')
		i++;
	if (env_var_source[i] == '=')
	{
		i++;
		var_value_len = ft_strlen(env_var_source) - i;
		var_value = ft_substr(env_var_source, i, var_value_len);
		if (var_value == NULL)
			*is_error = TRUE;
	}
	return (var_value);
}


static char	*extract_env_var_name(char *env_var_source, int *is_error)
{
	char	*var_name;
	int		i;

	i = 0;
	var_name = NULL;
	while (env_var_source[i] && env_var_source[i] != '=')
		i++;
	var_name = ft_substr(env_var_source, 0, i);
	if (var_name == NULL)
		*is_error = TRUE;
	return (var_name);
}

static void	free_env_var(void *env_var)
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

static t_list	**set_env_ver_to_list(t_list **env_lists, t_env_var *env_var)
{
	t_list	*new_env_list;

	new_env_list = ft_lstnew(env_var);
	if (!new_env_list)
	{
		free_env_var((void *)env_var);
		return (NULL);
	}
	ft_lstadd_back(env_lists, new_env_list);
	return (env_lists);
}

static t_env_var	*get_env_var(char *env_var_source)
{
	char		*env_var_name;
	char		*env_var_value;
	t_env_var	*env_var;
	int			is_error;

	is_error = FALSE;
	env_var_name = extract_env_var_name(env_var_source, &is_error);
	env_var_value = extract_env_var_value(env_var_source, &is_error);
	if (!env_var_name || is_error)
		return (NULL);
	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
	{
		free(env_var_name);
		free(env_var_value);
		return (NULL);
	}
	env_var->name = env_var_name;
	env_var->value = env_var_value;
	return (env_var);
}

t_list	*init_envlst(char **env)
{
	int			i;
	t_list		*env_lists;
	t_env_var	*env_var;

	if (!env)
		return (NULL);
	i = 0;
	env_lists = NULL;
	while (env[i])
	{
		env_var = get_env_var(env[i]);
		if (!env_var)
		{
			ft_lstclear(&env_lists, free_env_var);
			return (NULL);
		}
		if (!set_env_ver_to_list(&env_lists, env_var))
		{
			ft_lstclear(&env_lists, free_env_var);
			return (NULL);
		}
		i++;
	}
	return (env_lists);
}