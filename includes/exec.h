/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 00:13:37 by katakada          #+#    #+#             */
/*   Updated: 2025/05/23 01:35:25 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

// This is saved stdout and stdin
typedef struct s_std
{
	int			saved_stdin;
	int			saved_stdout;
}				t_std;
typedef enum e_err_msg
{
	NONE,
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_IS_DIRECTORY,
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

// err_msg (lib_func)
int				err_msg_malloc(void);

// err_msg (redirection)
int				err_msg_redirection(char *filename);

// err_msg (external)
int				err_msg_external(t_err err);
int				msg_ambiguous(t_err err);
int				msg_perm_denied(t_err err);
int				msg_no_such_file(t_err err);
int				msg_cmd_not_found(t_err err);
int				msg_is_directory(t_err err);

// prototypes exec
int				exec_cmd(t_abs_node *abs, t_env *env, t_std std);
int				exec_cmd_external(t_abs_node *node, char *envp[]);
int				exec_cmd_builtin(char **args, t_env *env);
int				exec_redirection(t_abs_node *node);
t_path			get_path(char *cmd);
t_path			create_t_path(char *cmd, int err_exit_s, int err_msg,
					char *err_cause);
t_err			create_t_err(int err_exit_s, int err_msg, char *err_cause);

// test_utils (exec)
t_abs_node		*abs_init(void);

#endif