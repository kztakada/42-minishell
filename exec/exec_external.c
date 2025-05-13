/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 21:45:09 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/06 13:29:24 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	exec_external(t_abs_node *node, t_minishell *minishell)
{
	int		status;
	pid_t	pid;
	t_path	path;

	minishell->sig_child = TRUE;
	pid = fork();
	if (!pid)
	{
		// リダイレクトの実装は後回し
		path = get_path(node->expanded_args[0]);
		if (path.err.no != ENO_SUCCESS)
		{
			status = err_msg(path.err);
			exit(status);
		}
		if (execve(path.path, node->expanded_args, minishell->envp) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	minishell->sig_child = FALSE;
	return (get_exit_status(status));
}
