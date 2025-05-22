/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:56:46 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/22 02:59:53 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINISHELL_H
# define H_MINISHELL_H

// prompt
# define PROMPT "minishell$ "

// includes
# include "../libraries/libft.h"
# include "minishell.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>

// test includes
#include <stdbool.h>

// This is saved stdout and stdin
typedef struct s_std
{
	int		saved_stdin;
	int		saved_stdout;
}	t_std;

typedef enum e_err_msg
{
	NONE,
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_IS_DIRECTORY,
}	t_err_msg;

typedef struct s_err
{
	int			exit_s;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

// abs node
typedef enum e_redirection_op_type
{
	RE_OP_HEREDOC, // <<
	RE_OP_APPEND, // >>
	RE_OP_INPUT,  // <
	RE_OP_OUTPUT, // >
}							t_redirection_op_type;

// filename is t_parsed_text list
typedef struct s_redirection
{
	t_redirection_op_type		type;
	int						fd;
	t_list					*file_name; // こっちはparsingの都合上残してあるだけ
	char					*expanded_file_name; //こっちしか使わない。
}							t_redirection;
// abs_node ****************************************************
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	BINOP_AND,
	BINOP_OR,
	PIPE,
	COMMAND
}							t_abs_node_type;

// command_args is list of t_parsed_text
// redirection_list is list of t_redirection
struct						s_abs_node
{
	t_abs_node_type			type;
	t_list					*command_args;
	char					**expanded_args;
	t_list					*redirection_list;
	t_abs_node				*left;
	t_abs_node				*right;
};

// prototypes builtins
int		ft_cd(char *path, t_list *env_list);
int		ft_echo(char **args);
int		ft_env(t_list *env_list);
int		ft_exit(char **args, t_exit_status exit_s);
int		ft_export(char **argv, t_list *env_list);
int		ft_pwd(void);
int		ft_unset(char **args, t_list *env_list);
t_bool	create_add_new_env(t_list **env_lst, char *name, char *value);
t_bool	update_env_value(t_list **env_lst, char *name, char *value);
int		is_alredy_exist(t_list *env_lst, char *name);
int		check_name_error(char *arg);

//prototypes exec
int			exec_cmd(t_abs_node *abs, t_env *env, t_std std);
int			exec_cmd_external(t_abs_node *node, char *envp[]);
int			exec_cmd_builtin(char **args, t_env *env);
int			exec_redirection(t_abs_node *node);
t_path		get_path(char *cmd);
t_path		create_t_path(char *cmd, int err_exit_s,
			int err_msg, char *err_cause);
t_err		create_t_err(int err_exit_s, int err_msg, char *err_cause);

// err_msg (builtin)
int			cd_err_msg_file(char *path);
int			cd_err_msg_home(void);
int			export_err_msg(char *arg);
int			unset_err_msg(char *arg);
void		exit_err_msg_digit(char *arg);
void		exit_err_msg_format(void);

// err_msg (external)
int			err_msg_external(t_err err);
int			msg_ambiguous(t_err err);
int			msg_perm_denied(t_err err);
int			msg_no_such_file(t_err err);
int			msg_cmd_not_found(t_err err);
int 		msg_is_directory(t_err err);

// err_msg (lib_func)
int		err_msg_malloc(void);

// err_msg (redirection)
int 	err_msg_redirection(char *filename);

// test_utils (exec)
t_abs_node		*abs_init(void);

//test_utils (builtins)
t_list	*init_envlst(char **env);

#endif