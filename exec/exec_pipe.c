/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:12:10 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/05 02:53:29 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	wait_child_process(pid_t pid_left, pid_t pid_right)
{
	int	status;

	if (waitpid(pid_left, &status, 0) == -1)
		return (perror(ERROR_WAITPID), EXIT_S_FAILURE);
	if (waitpid(pid_right, &status, 0) == -1)
		return (perror(ERROR_WAITPID), EXIT_S_FAILURE);
	return (get_exit_status(status));
}

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

static void	exec_pipe_left(t_abs_node *abs_tree, t_env *env, t_saved_std *std,
			int pfds[2])
{
	int	status;

	redirect_to_pipe(pfds, PIPE_WRITE_MODE);
	status = exec_abs(abs_tree->left, env, std, TRUE);
	exit(status);
}

static void	exec_pipe_right(t_abs_node *abs_tree, t_env *env, t_saved_std *std,
			int pfds[2])
{
	int	status;

	redirect_to_pipe(pfds, PIPE_READ_MODE);
	status = exec_abs(abs_tree->right, env, std, TRUE);
	exit(status);
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
		exec_pipe_left(abs_tree, env, std, pfds);
	else
	{
		pid_right = fork();
		if (pid_right == -1)
			return (perror(ERROR_FORK), EXIT_S_FAILURE);
		if (pid_right == 0)
			exec_pipe_right(abs_tree, env, std, pfds);
		else
			return (close(pfds[0]), close(pfds[1]),
				wait_child_process(pid_left, pid_right));
	}
	return (EXIT_S_FAILURE);
}
