/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/02 04:44:13 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static t_list	*copy_env_list(t_list *env_list)
{
	t_list		*new;
	t_list		*env_list_cpy;


	env_list_cpy = NULL;
	while (env_list)
	{
		new = ft_lstnew(env_list->content);
		if (!new)
			return (NULL);
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
			printf("declare -x %s=\"", env->name);
			i = 0;
			while ((env->value)[i])
			{
				if ((env->value)[i] == '$' || (env->value)[i] == '"')
					printf("\\%c", (env->value)[i++]);
				else
					printf("%c", (env->value)[i++]);
			}
			printf("\"\n");
		}
		else if (env->value == NULL && (ft_strcmp(env->name, "_") != 0))
			printf("declare -x %s\n", env->name);
		env_list = env_list->next;
	}
	return (EXIT_SUCCESS);
}

static void	update_env_list(char *arg, t_list *env_list)
{
	char	*name;
	char	*value;

	if (!ft_strchr(arg, '='))
	{
		name = ft_strdup(arg);
		value = NULL;
	}
	else
	{
		name = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_strchr(arg, '=') + 1;
	}
	if (is_env_exist(env_list, name))
		update_env_value(&env_list, name, value);
	else
		create_add_new_env(&env_list, name, value);
	free(name);
	return ;
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
			return (err_msg_malloc());
		sort_env_vars_by_ascending(&env_list_cpy);
		tmp_status = print_env_list(env_list_cpy);
		ft_lstclear(&env_list_cpy, free_env_var);
		return (tmp_status);
	}
	i = 1;
	tmp_status = EXIT_SUCCESS;
	while (argv[i])
	{
		if (check_name_error(argv[i]))
			tmp_status = export_err_msg(argv[i]);
		else
			update_env_list(argv[i], env_list);
		i++;
	}
	return (tmp_status);
}
