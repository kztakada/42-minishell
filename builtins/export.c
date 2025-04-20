/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:37 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/17 18:22:26 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static int	print_env_list(t_minishell *minishell)
{
	t_env	*env_lst;
	size_t	i;

	env_lst = minishell->env_lst;
	while (env_lst)
	{
		if (env_lst->value != NULL && (ft_strcmp(env_lst->key, "_") != 0))
		{
			printf("declare -x %s=\"", env_lst->key);
			i = 0;
			while ((env_lst->value)[i])
			{
				if ((env_lst->value)[i] == '$' || (env_lst->value)[i] == '"')
					printf("\\%c", (env_lst->value)[i++]);
				else
					printf("%c", (env_lst->value)[i++]);
			}
			printf("\"\n");
		}
		else if (env_lst->value == NULL && (ft_strcmp(env_lst->key, "_") != 0))
			printf("declare -x %s\n", env_lst->key);
		env_lst = env_lst->next;
	}
	return (EXIT_SUCCESS);
}

static void	update_env_lst(char *arg, t_env *env_lst)
{
	char	*key;
	char	*value;

	if (!ft_strchr(arg, '='))
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	else
	{
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
		value = ft_strchr(arg, '=') + 1;
	}
	if (is_alredy_exist(env_lst, key))
		update_env_value(&env_lst, key, value);
	else
		create_add_new_env(&env_lst, key, value);
	free(key);
	return ;
}

static int	export_err_msg(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (EXIT_FAILURE);
}

int	ft_export(char **argv, t_minishell *minishell)
{
	int	i;
	int	tmp_status;

	if (!argv[1])
		return (print_env_list(minishell));
	i = 1;
	tmp_status = EXIT_SUCCESS;
	while (argv[i])
	{
		if (check_key_error(argv[i]))
			tmp_status = export_err_msg(argv[i]);
		else
			update_env_lst(argv[i], minishell->env_lst);
		i++;
	}
	return (tmp_status);
}
