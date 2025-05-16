/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/16 11:53:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// // exec_cmd_external
// int main(int ac, char *av[], char *envp[])
// {
// 	(void)ac;
// 	(void)av;
// 	t_minishell minishell = minishell_init(envp);
// 	t_abs_node		*node = abs_init();
// 	exec_cmd_external(node, &minishell);
// 	free (node->expanded_args);
// 	free (node);
// }

// check_redirection
int main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	t_abs_node		*abs = abs_init();
	t_minishell minishell = minishell_init(envp);
	if (abs->redirection_list)
		exec_redirection(abs);
	exec_cmd_builtin(abs->expanded_args, &minishell);
	return (0);
}
