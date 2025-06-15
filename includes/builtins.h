/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:32:47 by katakada          #+#    #+#             */
/*   Updated: 2025/06/15 07:52:15 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// err_msg (builtin)
int		env_err_msg_path_env(void);
int		cd_err_msg_no_file(char *path);
int		cd_err_msg_permission(char *path);
int		cd_err_msg_home(void);
int		cd_err_msg_args(void);
int		cd_err_msg_is_file(char *path);
int		export_err_msg(char *arg);
int		unset_err_msg(char *arg);
int		exit_err_msg_digit(char *arg);
int		exit_err_msg_format(void);

// prototypes builtins
int		ft_cd(char **args, t_list *env_list, t_bool *unset_oldpwd);
int		ft_echo(char **args);
int		ft_env(t_list *env_list);
int		ft_export(char **argv, t_list *env_list, t_bool is_interactive);
int		ft_pwd(t_list *env_list);
int		ft_unset(char **args, t_list *env_list, t_bool *unset_oldpwd);
int		check_name_error(char *arg);
void	ft_exit(char **args, t_env *env, t_exit_status exit_s);
int		exec_cd(char *path, t_list *env_list, t_bool *unset_oldpwd,
			char *err_msg);
int		update_oldpwd_env(t_list *env_list, t_bool *unset_oldpwd);
int		update_pwd_env(t_list *env_list);

// export_utils.c
t_bool	is_valid_env_name(char *name, t_bool is_interactive);
void	put_export_declare(char *name);
void	put_export_escape_value(char value_c);
void	put_export_declare_null(char *name);

#endif