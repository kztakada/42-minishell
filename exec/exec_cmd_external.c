/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:59:24 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/28 15:42:29 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_cmd_external(t_abs_node *abs_tree, char *envp[])
{
	int		status;
	pid_t	pid;
	t_path	path;

	// シグナルの処理は後回し
	pid = fork();
	if (!pid)
	{
		status = exec_redirection(abs_tree->redirections);
		if (status != EXIT_S_SUCCESS)
			exit(status);
		path = get_path(abs_tree->expanded_args[0]);
		if (path.err.exit_s != EXIT_S_SUCCESS)
		{
			status = err_msg_external(path.err);
			exit(status);
		}
		if (execve(path.path, abs_tree->expanded_args, envp) == -1)
			exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
