/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:59:24 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/22 04:01:04 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	exec_cmd_external(t_abs_node *node, char *envp[])
{
	int		status;
	pid_t	pid;
	t_path	path;

	// シグナルの処理は後回し
	pid = fork();
	if (!pid)
	{
		status = exec_redirection(node);
		if (status != EXIT_S_SUCCESS)
			exit(status);
		path = get_path(node->expanded_args[0]);
		if (path.err.exit_s != EXIT_S_SUCCESS)
		{
			status = err_msg_external(path.err);
			exit(status);
		}
		if (execve(path.path, node->expanded_args, envp) == -1)
			exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
