/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/30 00:23:53 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// // exec_external
// int main(int ac, char *av[], char *envp[])
// {
// 	(void)ac;
// 	(void)av;
// 	t_minishell minishell = minishell_init(envp);
// 	t_node		*node = node_init();
// 	exec_external(node, &minishell);
// 	free (node->expanded_args);
// 	free (node);
// }

// check_redirection
int main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	t_minishell minishell = minishell_init(envp);
	t_node		*node = node_init();
	return (0);
}
