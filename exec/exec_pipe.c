/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:12:10 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 16:59:43 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_for_minishell.h"

static void	redirect_to_pipe(int pfds[2], t_pipe_access_mode mode)
{
	if (mode == PIPE_WRITE_MODE)
	{
		close(pfds[0]);
		dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	else if (mode == PIPE_READ_MODE)
	{
		close(pfds[1]);
		dup2(pfds[0], STDIN_FILENO);
		close(pfds[0]);
	}
	return ;
}

static void	exec_pipe_child_left(t_abs_node *abs_tree, t_env *env,
		t_saved_std *std, int pfds[2])
{
	int	status;

	set_sig_handlers_in_exec_child();
	redirect_to_pipe(pfds, PIPE_WRITE_MODE);
	status = exec_abs(abs_tree->left, env, std, TRUE);
	reset_stds(std, FALSE);
	clean_and_exit(status, env);
}

static void	exec_pipe_child_right(t_abs_node *abs_tree, t_env *env,
		t_saved_std *std, int pfds[2])
{
	int	status;

	set_sig_handlers_in_exec_child();
	redirect_to_pipe(pfds, PIPE_READ_MODE);
	status = exec_abs(abs_tree->right, env, std, TRUE);
	reset_stds(std, FALSE);
	clean_and_exit(status, env);
}

static int	handle_pipe_parent(int pfds[2], pid_t pid_left, pid_t pid_right)
{
	int	status_left;
	int	status_right;

	close(pfds[0]);
	close(pfds[1]);
	if (waitpid(pid_left, &status_left, 0) == -1)
		return (perror(ERROR_WAITPID), EXIT_S_FAILURE);
	if (waitpid(pid_right, &status_right, 0) == -1)
		return (perror(ERROR_WAITPID), EXIT_S_FAILURE);
	return (get_exit_status(status_right));
}

int	exec_pipe(t_abs_node *abs_tree, t_env *env, t_saved_std *std)
{
	int		pfds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(pfds) == -1)
		return (perror(ERROR_PIPE), EXIT_S_FAILURE);
	pid_left = fork();
	if (pid_left == -1)
		return (perror(ERROR_FORK), EXIT_S_FAILURE);
	if (pid_left == 0)
		exec_pipe_child_left(abs_tree, env, std, pfds);
	else
	{
		pid_right = fork();
		if (pid_right == -1)
			return (perror(ERROR_FORK), EXIT_S_FAILURE);
		if (pid_right == 0)
			exec_pipe_child_right(abs_tree, env, std, pfds);
		else
			return (handle_pipe_parent(pfds, pid_left, pid_right));
	}
	return (EXIT_S_FAILURE);
}
