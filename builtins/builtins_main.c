/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:10 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/18 14:59:30 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

#ifndef TEST

// // pwdコマンド
// int main(void)
// {
// 	ft_pwd();
// 	return (0);
// }

// // echoコマンド
// int main()
// {
// 	// normal case
// 	char *test_1[] = {"echo", "-n", "Hello", "World", NULL};
// 	ft_echo(test_1);

// 	// n_flag case
// 	char *test_2[] = {"echo", "-n", "-n", NULL};
// 	ft_echo(test_2);

// 	// complex case
// 	char *test_3[] = {"echo", "-n", "-n", "-nHello", "-n", NULL};
// 	ft_echo(test_3);

// }


// // // cdコマンド
// int main(int ac, char *av[], char *envp[])
// {
// 	(void)ac;
// 	(void)av;
// 	// home
// 	char *path = NULL;
// 	t_minishell minishell = minishell_init(envp);
// 	ft_cd(path, &minishell);
// 	ft_pwd();
// 	ft_env(&minishell);
// 	return (0);

// 	// normal
// 	char *path = "objs";
// 	t_minishell minishell = minishell_init(envp);
// 	ft_cd(path, &minishell);
// 	ft_pwd();
// 	ft_env(&minishell);
// 	return (0);

// 	// error
// 	char *path = "HHHH";
// 	t_minishell minishell = minishell_init(envp);
// 	ft_cd(path, &minishell);
// 	ft_pwd();
// 	ft_env(&minishell);
// 	return (0);
// }

// // envコマンド
// int main(void)
// {
// 	t_minishell minishell = minishell_init(envp);
// 	ft_env(&minishell);
// 	return (0);
// }

// // exportコマンド
// int main(int ac, char *av[], char *envp[])
// {
// 	(void)ac;
// 	(void)av;
// 	// // no argument
// 	// char **expo;

// 	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
// 	// expo[0] = "export";
// 	// expo[1] = NULL;
// 	// expo[2] = NULL;
// 	// t_minishell minishell = minishell_init(envp);
// 	// ft_export(expo, &minishell);
// 	// free(expo);

// 	// // normal (already exist)
// 	// char **expo;

// 	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
// 	// expo[0] = "export";
// 	// expo[1] = "TEST=HELLO";
// 	// expo[2] = NULL;
// 	// t_minishell minishell = minishell_init(envp);
// 	// ft_export(expo, &minishell);
// 	// ft_env(&minishell);
// 	// free (expo);

// 	// // normal (key has no value)
// 	// char **expo;

// 	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
// 	// expo[0] = "export";
// 	// expo[1] = "TEST";
// 	// expo[2] = NULL;
// 	// t_minishell minishell = minishell_init(envp);
// 	// ft_export(expo, &minishell);
// 	// ft_env(&minishell);
// 	// free (expo);

// 	// // several argument
// 	// char **expo;

// 	// expo = (char **)malloc(sizeof(char *) * (4 + 1));
// 	// expo[0] = "export";
// 	// expo[1] = "A";
// 	// expo[2] = "B=1";
// 	// expo[3] = "C=2";
// 	// expo[4] = NULL;
// 	// t_minishell minishell = minishell_init(envp);
// 	// ft_export(expo, &minishell);
// 	// ft_env(&minishell);
// 	// free (expo);

// 	// // error
// 	// char **expo;

// 	// expo = (char **)malloc(sizeof(char *) * (2 + 1));
// 	// expo[0] = "export";
// 	// expo[1] = "TEST = HELLO";
// 	// expo[2] = NULL;
// 	// t_minishell minishell = minishell_init(envp);
// 	// ft_export(expo, &minishell);
// 	// free (expo);
// }


// // unset
// int main(int ac, char *av[], char *envp[])
// {
// 	(void)ac;
// 	(void)av;
// 	// normal
// 	char **expo;
// 	char **unset;

// 	expo = (char **)malloc(sizeof(char *) * (2 + 1));
// 	unset = (char **)malloc(sizeof(char *) * (2 + 1));
// 	expo[0] = "export";
// 	expo[1] = "A=1";
// 	expo[2] = NULL;
// 	unset[0] = "unset";
// 	unset[1] = "A";
// 	unset[2] = NULL;
// 	t_minishell minishell = minishell_init(envp);
// 	ft_export(expo, &minishell);
// 	ft_env(&minishell);
// 	printf("\n-----------------------------------------------------------------------------\n\n");
// 	ft_unset(unset, &minishell);
// 	ft_env(&minishell);
// 	free(expo);
// 	free(unset);

// 	// no match
// 	char **unset;

// 	unset = (char **)malloc(sizeof(char *) * (2 + 1));
// 	unset[0] = "unset";
// 	unset[1] = "NNNNN";
// 	unset[2] = NULL;
// 	t_minishell minishell = minishell_init(envp);
// 	ft_unset(unset, &minishell);
// 	ft_env(&minishell);
// 	free(unset);

// 	// format error
// 	char **unset;

// 	unset = (char **)malloc(sizeof(char *) * (2 + 1));
// 	unset[0] = "unset";
// 	unset[1] = "1TEST";
// 	unset[2] = NULL;
// 	t_minishell minishell = minishell_init(envp);
// 	ft_unset(unset, &minishell);
// 	ft_env(&minishell);
// 	free(unset);
// }

// // exit
// void check_exit(void) // mainが終了したら呼び出される
// {
// 	printf("success exit\n");
// }

// int main(int ac, char *av[], char *envp[])
// {
	// int i;
	// char **args;


	// (void)ac;
	// (void)av;
	// i = atexit(check_exit); // 正常終了時に呼び出される関数を設定
	// if (i != 0) {
	// 	fprintf(stderr, "cannot set exit function\n");
	// 	exit(EXIT_FAILURE);
	// }
	// t_minishell minishell = minishell_init(envp);
	// // normal (using last exit status)
	// args = (char **)malloc(sizeof(char *) * (2 + 1));
	// args[0] = "exit";
	// args[1] = NULL;
	// args[2] = NULL;
	// ft_exit(args, &minishell);

	// // error (too argument)
	// args = (char **)malloc(sizeof(char *) * (3 + 1));
	// args[0] = "exit";
	// args[1] = "3";
	// args[2] = "EEE";
	// args[3] = NULL;
	// ft_exit(args, &minishell);

	// // error (not valid second argument)
	// args = (char **)malloc(sizeof(char *) * (2 + 1));
	// args[0] = "exit";
	// args[1] = "HHH";
	// args[3] = NULL;
	// ft_exit(args, &minishell);
// }

#endif // TEST
