/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:14:40 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/15 19:27:30 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// // exec_cmd_external(absolute path success)
// t_abs_node	*abs_init(void)
// {
// 	t_abs_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
// 	node->expanded_args[0] = "/bin/ls";
// 	node->expanded_args[1] = "-l";
// 	node->expanded_args[2] = NULL;
// 	node->type = COMMAND;
// 	node->cmd_args = "/bin/ls -l";
// 	node->redirect_list = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_cmd_external(relative path success)
// t_node	*abs_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
// 	node->expanded_args[0] = "ls";
// 	node->expanded_args[1] = "-l";
// 	node->expanded_args[2] = NULL;
// 	node->type = COMMAND;
// 	node->cmd_args = "ls -l";
// 	node->redirect_list = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_cmd_external(absolute cmd not found)
// t_node	*abs_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (1 + 1));
// 	node->expanded_args[0] = "asd/dfa";
// 	node->expanded_args[1] = NULL;
// 	node->type = COMMAND;
// 	node->cmd_args = "asd/dfa";
// 	node->redirect_list = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_cmd_external(relative cmd not found)
// t_node	*abs_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (1 + 1));
// 	node->expanded_args[0] = "dfa";
// 	node->expanded_args[1] = NULL;
// 	node->type = COMMAND;
// 	node->cmd_args = "dfa";
// 	node->redirect_list = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_cmd_external(absolute permission denied)
// t_node	*abs_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (1 + 1));
// 	node->expanded_args[0] = "/Users/kharuya/test.sh";
// 	node->expanded_args[1] = NULL;
// 	node->type = COMMAND;
// 	node->cmd_args = "/Users/kharuya/test.sh";
// 	node->redirect_list = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// }

// // exec_cmd_external(execve error)
// t_node	*abs_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
// 	node->expanded_args[0] = "ls";
// 	node->expanded_args[1] = "dfa";
// 	node->expanded_args[2] = NULL;
// 	node->type = COMMAND;
// 	node->cmd_args = "ls dfa";
// 	node->redirect_list = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// redirect (builtins)
t_abs_node	*abs_init(void)
{
    t_abs_node	*node = (t_abs_node *)malloc(sizeof(t_abs_node));
    t_redirect	*redirect;

    if (!node)
        return (NULL); // メモリ確保失敗時のエラーハンドリング

    // ノードの初期化
    node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
    if (!node->expanded_args)
    {
        free(node);
        return (NULL);
    }
    node->expanded_args[0] = strdup("echo");
    node->expanded_args[1] = strdup("AAA");
    node->expanded_args[2] = NULL;

    // リダイレクトリストの初期化
    node->redirect_list = (t_list *)malloc(sizeof(t_list));
    if (!node->redirect_list)
    {
        free(node->expanded_args[0]);
        free(node->expanded_args[1]);
        free(node->expanded_args);
        free(node);
        return (NULL);
    }

    redirect = (t_redirect *)malloc(sizeof(t_redirect));
    if (!redirect)
    {
        free(node->redirect_list);
        free(node->expanded_args[0]);
        free(node->expanded_args[1]);
        free(node->expanded_args);
        free(node);
        return (NULL);
    }

    redirect->type = RE_OP_OUTPUT;
    redirect->fd = 0;
    redirect->file_name = NULL;
    redirect->expanded_file_name = strdup(""); // strdupでコピー
    if (!redirect->expanded_file_name)
    {
        free(redirect);
        free(node->redirect_list);
        free(node->expanded_args[0]);
        free(node->expanded_args[1]);
        free(node->expanded_args);
        free(node);
        return (NULL);
    }

    node->redirect_list->content = redirect;
    node->redirect_list->next = NULL; // nextをNULLで初期化

    // その他のフィールドの初期化
    node->type = COMMAND;
    node->command_args = NULL;
    node->left = NULL;
    node->right = NULL;

    return (node);
}
