/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 15:12:10 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/28 16:24:58 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	wait_child_process(pid_t pid_left, pid_t pid_right)
{
	int	status;

	waitpid(pid_left, &status, 0);
	waitpid(pid_right, &status, 0);
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

static void	exec_pipe_left(t_abs_node *abs_tree, t_env *env, t_saved_std std,
			int pfds[2])
{
	int	status;

	redirect_to_pipe(pfds, PIPE_WRITE_MODE);
	status = exec_abs(abs_tree->left, env, std, TRUE);
	exit(status);
}

static void	exec_pipe_right(t_abs_node *abs_tree, t_env *env, t_saved_std std,
			int pfds[2])
{
	int	status;

	redirect_to_pipe(pfds, PIPE_READ_MODE);
	status = exec_abs(abs_tree->right, env, std, TRUE);
	exit(status);
}

int	exec_pipe(t_abs_node *abs_tree, t_env *env, t_saved_std std)
{
	int		pfds[2];
	pid_t	pid_left;
	pid_t	pid_right;

	// シグナルの処理は後回し
	pipe(pfds);
	pid_left = fork();
	if (pid_left == 0)
		exec_pipe_left(abs_tree, env, std, pfds);
	else
	{
		pid_right = fork();
		if (pid_right == 0)
			exec_pipe_right(abs_tree, env, std, pfds);
		else
		{
			close(pfds[0]);
			close(pfds[1]);
			return (wait_child_process(pid_left, pid_right));
		}
	}
	return (EXIT_S_FAILURE);
}
