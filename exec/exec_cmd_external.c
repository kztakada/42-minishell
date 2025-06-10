/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:59:24 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/08 05:33:47 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_for_minishell.h"

int	exec_cmd_external(t_abs_node *abs_tree, t_list *env_vars, t_env *env)
{
	int		status;
	pid_t	pid;
	t_path	path;
	char	**envp;

	pid = fork();
	if (pid == -1)
		return (perror(ERROR_FORK), EXIT_S_FAILURE);
	if (pid == 0)
	{
		set_sig_handlers_in_exec_child();
		status = exec_redirection(abs_tree->redirections);
		if (status != EXIT_S_SUCCESS)
			clean_and_exit(status, env);
		path = get_path(abs_tree->expanded_args[0], env_vars);
		if (path.err.exit_s != EXIT_S_SUCCESS)
			clean_and_exit(err_msg_external(path.err), env);
		envp = convert_list_to_envp(env_vars);
		if (!envp)
		{
			perror(ERROR_MALLOC);
			clean_and_exit(EXIT_S_FAILURE, env);
		}
		if (execve(path.path, abs_tree->expanded_args, envp) == -1)
		{
			perror(ERROR_EXECVE);
			clean_and_exit(EXIT_S_FAILURE, env);
		}
	}
	set_sig_handlers_in_exec_parent();
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
