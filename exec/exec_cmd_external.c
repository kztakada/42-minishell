/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 03:59:24 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/13 21:51:08 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_for_minishell.h"

static void	handle_execve_error_and_exit(char *cmd, t_env *env, char **envp)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": line 1: This: command not found\n", STDERR_FILENO);
	ft_free_char2(envp);
	clean_and_exit(EXIT_S_FAILURE, env);
}

static void	handle_invalid_envp(t_env *env)
{
	perror(ERROR_MALLOC);
	clean_and_exit(EXIT_S_FAILURE, env);
}

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
			handle_invalid_envp(env);
		if (execve(path.path, abs_tree->expanded_args, envp) == -1)
			handle_execve_error_and_exit(abs_tree->expanded_args[0], env, envp);
	}
	waitpid(pid, &status, 0);
	return (get_exit_status(status));
}
