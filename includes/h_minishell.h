/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:56:46 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/15 02:17:42 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_MINISHELL_H
# define H_MINISHELL_H

// prompt
# define PROMPT "minishell$ "

// includes
# include "../libraries/libft.h"
# include <unistd.h>
# include <stdio.h>

// test includes
#include <stdbool.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}	t_bool;

//shell error
typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

//ft_cd
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	t_env	*env_lst;
} t_minishell;

// prototypes builtins
int		ft_cd(char *path, t_minishell *minishell);
int		ft_echo(char **args);
int		ft_env(t_minishell *minishell);
void	ft_exit(char **args);
int		ft_export(char **argv, t_minishell *minishell);
int		ft_pwd(void);
int		ft_unset(char **args);

// cd utils
void	create_new_env(t_env **env_lst, char *key, char *value);
void	update_env_value(t_env **env_lst, char *key, char *value);
int		is_alredy_exist(t_env *env_lst, char *key);

//prototypes exec
int		ft_exec_builtin(char **args);
// int		ft_check_redirection(t_node *node);

//test_utils
char	*ft_extract_key(char *str);
void	*ft_garbage_collector(void *ptr, bool clean);
char	*ft_extract_value(char *str);
void	ft_update_env_lst(char *key, char *value, bool create, t_env **env_lst);
void	ft_env_lst_back(t_env *new, t_env *env_lst);
t_env	*ft_env_lst_new(char *key, char *value);

#endif