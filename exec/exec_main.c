/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/20 04:16:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// check_redirection input (external)
int main(int ac, char *av[], char *envp[])
{
	(void)ac;
	(void)av;
	t_abs_node		*abs = abs_init();
	t_env	*env = (t_env *)malloc(sizeof(t_env) * 1);
	env->env_lists = init_envlst(envp);
	env->envp = envp;
	env->exit_status = 0;
	exec_redirection(abs);
	exec_cmd_builtin(abs->expanded_args, env);
	return (0);
}
