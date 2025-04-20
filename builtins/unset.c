/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:45 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/17 18:20:02 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static void	unset_env(char *key, t_minishell **minishell)
{
	t_env	*pre;
	t_env	*curr;

	pre = NULL;
	curr = (*minishell)->env_lst;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			if (pre)
				pre->next = curr->next;
			else
				(*minishell)->env_lst = curr->next;
			free(curr);
			return ;
		}
		pre = curr;
		curr = curr->next;
	}
	return ;
}

static int	unset_err_msg(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd("`", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (EXIT_FAILURE);
}

int	ft_unset(char **args, t_minishell *minishell)
{
	int	i;
	int	tmp_status;

	if (!args[1])
		return (EXIT_SUCCESS);
	i = 1;
	tmp_status = EXIT_SUCCESS;
	while (args[i])
	{
		if (check_key_error(args[i]))
			tmp_status = unset_err_msg(args[i]);
		else
			unset_env(args[i], &minishell);
		i++;
	}
	return (tmp_status);
}
