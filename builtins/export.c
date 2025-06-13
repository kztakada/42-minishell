/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 21:07:21 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static t_list	*copy_env_list(t_list *env_list)
{
	t_list		*new;
	t_list		*env_list_cpy;
	t_env_var	*content_cpy;

	env_list_cpy = NULL;
	while (env_list)
	{
		content_cpy = copy_deep_env_var(env_list->content);
		if (!content_cpy)
			return (NULL);
		new = ft_lstnew(content_cpy);
		if (!new)
			return (ft_lstclear(&env_list_cpy, free_env_var), NULL);
		ft_lstadd_back(&env_list_cpy, new);
		env_list = env_list->next;
	}
	return (env_list_cpy);
}

static void	sort_env_vars_by_ascending(t_list **env_vars)
{
	t_list		*current;
	t_list		*next;
	t_env_var	*current_env;
	t_env_var	*next_env;

	if (env_vars == NULL || *env_vars == NULL)
		return ;
	current = *env_vars;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			current_env = (t_env_var *)current->content;
			next_env = (t_env_var *)next->content;
			if (ft_strcmp(current_env->name, next_env->name) > 0)
				ft_swap(&current->content, &next->content);
			next = next->next;
		}
		current = current->next;
	}
}

static int	print_env_list(t_list *env_list)
{
	t_env_var	*env;
	size_t		i;

	while (env_list)
	{
		env = (t_env_var *)env_list->content;
		if (env->value != NULL && (ft_strcmp(env->name, "_") != 0))
		{
			put_export_declare(env->name);
			i = 0;
			while ((env->value)[i])
			{
				if ((env->value)[i] == '$' || (env->value)[i] == '"')
					put_export_escape_value((env->value)[i++]);
				else
					ft_putchar_fd((env->value)[i++], STDOUT_FILENO);
			}
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		else if (env->value == NULL && ft_strcmp(env->name, "_") != 0)
			put_export_declare_null(env->name);
		env_list = env_list->next;
	}
	return (EXIT_S_SUCCESS);
}

static int	update_env_list(char *arg, t_list *env_list)
{
	char	*name;
	char	*value;
	int		exit_status;

	if (!ft_strchr(arg, '='))
	{
		name = ft_strdup(arg);
		if (!name)
			return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
		value = NULL;
	}
	else
	{
		name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		if (!name)
			return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
		value = ft_strchr(arg, '=') + 1;
	}
	if (is_env_exist(env_list, name))
		exit_status = update_env_value(&env_list, name, value);
	else
		exit_status = create_add_new_env(&env_list, name, value);
	free(name);
	return (exit_status);
}

int	ft_export(char **argv, t_list *env_list)
{
	t_list	*env_list_cpy;
	int		i;
	int		tmp_status;

	if (!argv[1])
	{
		env_list_cpy = copy_env_list(env_list);
		if (!env_list_cpy)
			return (perror(ERROR_MALLOC), EXIT_S_FAILURE);
		sort_env_vars_by_ascending(&env_list_cpy);
		tmp_status = print_env_list(env_list_cpy);
		ft_lstclear(&env_list_cpy, free_env_var);
		return (tmp_status);
	}
	i = 1;
	tmp_status = EXIT_S_SUCCESS;
	while (argv[i])
	{
		if (check_name_error(argv[i]))
			tmp_status = export_err_msg(argv[i]);
		else
			tmp_status = update_env_list(argv[i], env_list);
		i++;
	}
	return (tmp_status);
}
