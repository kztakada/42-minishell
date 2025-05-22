/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:55:16 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/23 01:02:06 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// check_redirection input (external)
// int	main(int ac, char *av[], char *envp[])
// {
// 	t_abs_node	*abs;
// 	t_env		*env;

// 	(void)ac;
// 	(void)av;
// 	abs = abs_init();
// 	env = (t_env *)malloc(sizeof(t_env) * 1);
// 	env->env_vars = init_envlst(envp);
// 	env->envp = envp;
// 	env->exit_status = 0;
// 	exec_redirection(abs);
// 	exec_cmd_builtin(abs->expanded_args, env);
// 	return (0);
// }
