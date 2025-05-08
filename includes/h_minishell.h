/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:56:46 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/06 14:31:10 by kharuya          ###   ########.fr       */
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

// test includes
#include <stdbool.h>

typedef enum e_err_msg
{
	NONE,
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// abs node
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	BINARY_OP, // 二項演算子（&&、||、|など）
	REDIRECT, // リダイレクション（>、>>、<、<<など）
	SUBSHELL, // サブシェル（(command)などの括弧）
	COMMAND // 実行可能なコマンドを表すノード
}							t_abs_node_type;

typedef struct s_redirection
{
	char					*value; // リダイレクトの元の文字列（> output.txtなど）
	char					**expanded_value; // リダイレクトの元の文字列を単語ごとに分けた二次元文字列（>、output.txtなど）
	int						here_doc; // heredoc用
}							t_redirection;

struct						s_abs_node
{
	t_abs_node_type			node_type; // ノードの種類
	t_token					*token; // ノードに関連づけられたトークン（コマンドや演算子）
	t_list					*redirection_list; // リダイレクト情報のリスト
	char					*cmd_args; // コマンドの引数を表す文字列
	char					**expanded_args; // コマンドの引数を単語ごとに分けた二次元文字列
	t_abs_node				*left;
	t_abs_node				*right;
};

typedef struct s_minishell
{
	t_env	*env_lst;
	char	**envp;
	int		exit_s;
	int		sig_child;
}	t_minishell;

// prototypes builtins
int		ft_cd(char *path, t_minishell *minishell);
int		ft_echo(char **args);
int		ft_env(t_minishell *minishell);
int		ft_exit(char **args, t_minishell *minishell);
int		ft_export(char **argv, t_minishell *minishell);
int		ft_pwd(void);
int		ft_unset(char **args, t_minishell *minishell);
void	create_add_new_env(t_env **env_lst, char *key, char *value);
void	update_env_value(t_env **env_lst, char *key, char *value);
int		is_alredy_exist(t_env *env_lst, char *key);
int		check_key_error(char *arg);

//test_utils (builtins)
t_minishell	minishell_init(char **envp);
t_env 		*make_env_list(char **envp);
char		*ft_extract_key(char *str);
void		*ft_garbage_collector(void *ptr, bool clean);
char		*ft_extract_value(char *str);
void		ft_update_env_lst(char *key, char *value, bool create, t_env **env_lst);
void		ft_env_lst_back(t_env *new, t_env *env_lst);
t_env		*ft_env_lst_new(char *key, char *value);

//prototypes exec
int			exec_external(t_abs_node *node, t_minishell *minishell);
int			exec_builtin(char **args, t_minishell *minishell);
t_path		get_path(char *cmd);
int			err_msg(t_err err);
int			exec_redirection(t_abs_node node);

//test_utils (exec)
t_abs_node		*node_init(void);

#endif