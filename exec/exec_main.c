/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/19 15:18:55 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// ft_exec_child
int main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	t_minishell minishell = minishell_init(envp);
	t_node		*node = node_init();
	ft_exec_child(t_node *node, t_minishell *minishell);
	free (node->expanded_args);
	free (node);
}
