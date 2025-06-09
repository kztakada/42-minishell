/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 06:14:11 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/10 01:29:41 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_for_minishell.h"

int	exec_subshell(t_abs_node *abs_tree, t_env *env, t_saved_std *std)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror(ERROR_FORK), EXIT_S_FAILURE);
	if (pid == 0)
	{
		set_sig_handlers_in_exec_child();
		status = exec_redirection(abs_tree->redirections);
		if (status != EXIT_S_SUCCESS)
			return (status);
		status = exec_abs(abs_tree->left, env, std, TRUE);
		reset_stds(std, FALSE);
		exit(status);
	}
	set_sig_handlers_in_exec_parent();
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
