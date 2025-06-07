/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:32:47 by katakada          #+#    #+#             */
/*   Updated: 2025/06/08 02:05:33 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// err_msg (builtin)
int	env_err_msg_path_env(void);
int	cd_err_msg_file(char *path);
int	cd_err_msg_home(void);
int	export_err_msg(char *arg);
int	unset_err_msg(char *arg);
int	exit_err_msg_digit(char *arg);
int	exit_err_msg_format(void);

// prototypes builtins
int	ft_cd(char *path, t_list *env_list, t_bool *unset_oldpwd);
int	ft_echo(char **args);
int	ft_env(t_list *env_list);
int	ft_exit(char **args, t_exit_status exit_s);
int	ft_export(char **argv, t_list *env_list);
int	ft_pwd(void);
int	ft_unset(char **args, t_list *env_list, t_bool *unset_oldpwd);
int	check_name_error(char *arg);

#endif