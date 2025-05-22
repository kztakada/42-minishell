/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:14:40 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/23 00:57:52 by katakada         ###   ########.fr       */
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
// 	node->redirections = NULL;
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
// 	node->redirections = NULL;
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
// 	node->redirections = NULL;
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
// 	node->redirections = NULL;
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
// 	node->redirections = NULL;
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
// 	node->redirections = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // redirection (redirect_output_to_file)
// t_abs_node	*abs_init(void)
// {
//     t_abs_node	*node = (t_abs_node *)malloc(sizeof(t_abs_node));
//     t_redirection	*redirection;

//     if (!node)
//         return (NULL); // メモリ確保失敗時のエラーハンドリング

//     // ノードの初期化
//     node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
//     if (!node->expanded_args)
//     {
//         free(node);
//         return (NULL);
//     }
//     node->expanded_args[0] = strdup("echo");
//     node->expanded_args[1] = strdup("AAA");
//     node->expanded_args[2] = NULL;

//     // リダイレクトリストの初期化
//     node->redirections = (t_list *)malloc(sizeof(t_list));
//     if (!node->redirections)
//     {
//         free(node->expanded_args[0]);
//         free(node->expanded_args[1]);
//         free(node->expanded_args);
//         free(node);
//         return (NULL);
//     }

//     redirection = (t_redirection *)malloc(sizeof(t_redirection));
//     if (!redirection)
//     {
//         free(node->redirections);
//         free(node->expanded_args[0]);
//         free(node->expanded_args[1]);
//         free(node->expanded_args);
//         free(node);
//         return (NULL);
//     }

//     redirection->type = RE_OP_OUTPUT;
//     redirection->fd = 0;
//     redirection->file_name_words = NULL;
//     redirection->expanded_file_name = strdup("test.txt"); // strdupでコピー
//     if (!redirection->expanded_file_name)
//     {
//         free(redirection);
//         free(node->redirections);
//         free(node->expanded_args[0]);
//         free(node->expanded_args[1]);
//         free(node->expanded_args);
//         free(node);
//         return (NULL);
//     }

//     node->redirections->content = redirection;
//     node->redirections->next = NULL; // nextをNULLで初期化

//     // その他のフィールドの初期化
//     node->type = COMMAND;
//     node->cmd_words = NULL;
//     node->left = NULL;
//     node->right = NULL;

//     return (node);
// }

// redirection (redirect_input_from_file)
t_abs_node	*abs_init(void)
{
	t_abs_node		*node;
	t_redirection	*redirection;

	node = (t_abs_node *)malloc(sizeof(t_abs_node));
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
	node->redirections = (t_list *)malloc(sizeof(t_list));
	if (!node->redirections)
	{
		free(node->expanded_args[0]);
		free(node->expanded_args[1]);
		free(node->expanded_args);
		free(node);
		return (NULL);
	}
	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (!redirection)
	{
		free(node->redirections);
		free(node->expanded_args[0]);
		free(node->expanded_args[1]);
		free(node->expanded_args);
		free(node);
		return (NULL);
	}
	redirection->type = RE_OP_APPEND;
	redirection->fd = 0;
	redirection->file_name_words = NULL;
	redirection->expanded_file_name = strdup("test.txt"); // strdupでコピー
	if (!redirection->expanded_file_name)
	{
		free(redirection);
		free(node->redirections);
		free(node->expanded_args[0]);
		free(node->expanded_args[1]);
		free(node->expanded_args);
		free(node);
		return (NULL);
	}
	node->redirections->content = redirection;
	node->redirections->next = NULL; // nextをNULLで初期化
	// その他のフィールドの初期化
	node->type = ABS_COMMAND;
	node->cmd_words = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
