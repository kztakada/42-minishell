/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:10 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/15 15:34:36 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

static t_env *make_env_list(char **envp)
{
	int	i;
	char	*key;
	char	*value;
	t_env	*env_lst;

	env_lst = NULL;
	i = 0;
	while (envp[i])
	{
		key = ft_extract_key(envp[i]);
		value = ft_extract_value(envp[i]);
		ft_update_env_lst(key, value, true, &env_lst);
		i++;
	}
	return (env_lst);
}

static t_minishell minishell_init(char **envp)
{
	t_minishell minishell;

	ft_memset(&minishell, 0, sizeof(t_minishell));
	minishell.env_lst = make_env_list(envp);
	return (minishell);
}

#ifndef TEST

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;

	// // pwdコマンド
	// ft_pwd();
	// return (0);

	// // echoコマンド
	// // normal case
	// char *test_1[] = {"echo", "-n", "Hello", "World", NULL};
	// ft_echo(test_1);
	// // n_flag case
	// char *test_2[] = {"echo", "-n", "-n", NULL};
	// ft_echo(test_2);
	// // complex case
	// char *test_3[] = {"echo", "-n", "-n", "-nHello", "-n", NULL};
	// ft_echo(test_3);

	// // cdコマンド
	// // home
	// char *path = NULL;
	// t_minishell minishell = minishell_init(envp);
	// ft_cd(path, &minishell);
	// ft_pwd();
	// ft_env(&minishell);
	// return (0);
	// normal
	// char *path = "objs";
	// t_minishell minishell = minishell_init(envp);
	// ft_cd(path, &minishell);
	// ft_pwd();
	// ft_env(&minishell);
	// return (0);
	// // error
	// char *path = "HHHH";
	// t_minishell minishell = minishell_init(envp);
	// ft_cd(path, &minishell);
	// ft_pwd();
	// ft_env(&minishell);
	// while (minishell.env_lst)
	// {
	// 	printf("key:%s value:%s\n", minishell.env_lst->key, minishell.env_lst->value);
	// 	minishell.env_lst = minishell.env_lst->next;
	// }
	// return (0);

	// // envコマンド
	// // normal
	// t_minishell minishell = minishell_init(envp);
	// ft_env(&minishell);
	// return (0);

	// // exportコマンド
	// no argument
	char **expo1;
	char **expo2;

	expo1 = (char **)malloc(sizeof(char *) * (2 + 1));
	expo2 = (char **)malloc(sizeof(char *) * (2 + 1));
	expo1[0] = "export";
	expo1[1] = "PWD_CPY=$PWD";
	expo1[2] = NULL;
	expo2[0] = "export";
	expo2[1] = NULL;
	expo2[2] = NULL;
	t_minishell minishell = minishell_init(envp);
	ft_export(expo1, &minishell);
	ft_export(expo2, &minishell);
	free(expo1);
	free(expo2);
	// // normal (do or do not already exist)
	// char **expo;

	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
	// expo[0] = "export";
	// expo[1] = "TEST=HELLO";
	// expo[2] = NULL;
	// t_minishell minishell = minishell_init(envp);
	// ft_export(expo, &minishell);
	// ft_env(&minishell);
	// free (expo);
	// // normal (key has no value)
	// char **expo;

	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
	// expo[0] = "export";
	// expo[1] = "TEST";
	// expo[2] = NULL;
	// t_minishell minishell = minishell_init(envp);
	// ft_export(expo, &minishell);
	// ft_env(&minishell);
	// free (expo);
	// // error
	// char **expo;

	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
	// expo[0] = "export";
	// expo[1] = "TEST = HELLO";
	// expo[2] = NULL;
	// t_minishell minishell = minishell_init(envp);
	// ft_export(expo, &minishell);
	// free (expo);
}
#endif // TEST