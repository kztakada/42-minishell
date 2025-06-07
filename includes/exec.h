/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:37 by katakada          #+#    #+#             */
/*   Updated: 2025/06/08 05:30:57 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// pipe access mode
typedef enum e_pipe_access_mode
{
	PIPE_WRITE_MODE,
	PIPE_READ_MODE,
}				t_pipe_access_mode;


// This is saved stdout and stdin
typedef struct s_std
{
	int			saved_stdin;
	int			saved_stdout;
}				t_saved_std;
typedef enum e_err_msg
{
	NONE,
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_IS_DIRECTORY,
	ERRMSG_MALLOC,
}				t_err_msg;
typedef struct s_err
{
	int			exit_s;
	t_err_msg	msg;
	char		*cause;
}				t_err;
typedef struct s_path
{
	t_err		err;
	char		*path;
}				t_path;

// err_msg (redirection)
int				err_msg_redirection(char *filename);

// err_msg (external)
int				err_msg_external(t_err err);
int				msg_perm_denied(t_err err);
int				msg_no_such_file(t_err err);
int				msg_cmd_not_found(t_err err);
int				msg_is_directory(t_err err);

// prototypes exec
int				exec_abs(t_abs_node *abs_tree, t_env *env, t_saved_std *std, t_bool piped);
int				exec_cmd(t_abs_node *abs_tree, t_env *env, t_saved_std *std, t_bool piped);
int				exec_cmd_external(t_abs_node *abs_tree, t_list *env_vars, t_env *env);
int				exec_cmd_builtin(char **args, t_env *env);
int				exec_redirection(t_list	*redirection_list);
int				exec_pipe(t_abs_node *abs_tree, t_env *env, t_saved_std *std);
int				get_exit_status(int status);
t_path			get_path(char *cmd, t_list *env_vars);
t_path			create_t_path(char *cmd, int err_exit_s, int err_msg,
					char *err_cause);
t_err			create_t_err(int err_exit_s, int err_msg, char *err_cause);
char			**convert_list_to_envp(t_list *env_vars);

#endif