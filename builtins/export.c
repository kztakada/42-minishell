/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/28 17:11:56 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

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
	if (is_alredy_exist(env_list, name))
		update_env_value(&env_list, name, value);
	else
		create_add_new_env(&env_list, name, value);
	free(name);
	return ;
}

int	ft_export(char **argv, t_list *env_list)
{
	int	i;
	int	tmp_status;

	if (!argv[1])
		return (print_env_list(env_list));
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
