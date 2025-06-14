/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:45 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/14 17:35:35 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static void	unset_env(char *name, t_list **env_list)
{
	t_list		*pre;
	t_list		*curr;
	t_env_var	*env_curr;

	pre = NULL;
	curr = *env_list;
	while (curr)
	{
		env_curr = curr->content;
		if (!ft_strcmp(env_curr->name, name))
		{
			if (pre)
				pre->next = curr->next;
			else
				*env_list = curr->next;
			free_env_var(env_curr);
			free(curr);
			return ;
		}
		pre = curr;
		curr = curr->next;
	}
	return ;
}

int	ft_unset(char **args, t_list *env_list, t_bool *unset_oldpwd)
{
	int	i;
	int	tmp_status;

	if (!args[1])
		return (EXIT_S_SUCCESS);
	i = 1;
	tmp_status = EXIT_S_SUCCESS;
	while (args[i])
	{
		if (check_name_error(args[i]))
			tmp_status = unset_err_msg(args[i]);
		else if (ft_strcmp(args[i], "_") == 0)
			update_env_value(&env_list, "_", "_");
		else
		{
			unset_env(args[i], &env_list);
			if (!ft_strcmp(args[i], "OLDPWD") && *unset_oldpwd == FALSE)
				*unset_oldpwd = TRUE;
		}
		i++;
	}
	return (tmp_status);
}
