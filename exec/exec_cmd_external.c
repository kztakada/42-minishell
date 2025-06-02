/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:59:24 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/02 17:32:15 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_for_minishell.h"

int	exec_cmd_external(t_abs_node *abs_tree, t_list *env_vars)
{
	int		status;
	pid_t	pid;
	t_path	path;
	char	**envp;

	// シグナルの処理は後回し
	pid = fork();
	if (!pid)
	{
		set_sig_handlers_in_exec_child();
		status = exec_redirection(abs_tree->redirections);
		if (status != EXIT_S_SUCCESS)
			exit(status);
		path = get_path(abs_tree->expanded_args[0], env_vars);
		if (path.err.exit_s != EXIT_S_SUCCESS)
			exit(err_msg_external(path.err));
		envp = convert_list_to_envp(env_vars);
		if (!envp)
			exit(err_msg_malloc());
		if (execve(path.path, abs_tree->expanded_args, envp) == -1)
			exit(err_msg_execve());
		exit(EXIT_S_SUCCESS);
	}
	set_sig_handlers_in_exec_parent();
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
