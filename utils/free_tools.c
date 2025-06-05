/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 19:44:11 by katakada          #+#    #+#             */
/*   Updated: 2025/06/05 15:55:51 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_list(char **str_list)
{
	int	i;

	if (str_list == NULL)
		return ;
	i = 0;
	while (str_list[i] != NULL)
	{
		free(str_list[i]);
		i++;
	}
	free(str_list);
}

void	no_del(void *target)
{
	(void)target;
}

void	free_all_env(t_env env)
{
	ft_lstclear(&(env.env_vars), free_env_var);
	ft_lstclear(&(env.token_list), free_token);
	free_abs_tree(env.abs_tree);
	rl_clear_history();
}
