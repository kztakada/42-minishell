/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:14:40 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/06 14:32:31 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

// // exec_external(absolute path success)
// t_abs_node	*node_init(void)
// {
// 	t_abs_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
// 	node->expanded_args[0] = "/bin/ls";
// 	node->expanded_args[1] = "-l";
// 	node->expanded_args[2] = NULL;
// 	node->node_type = COMMAND;
// 	node->cmd_args = "/bin/ls -l";
// 	node->redirection_list = NULL;
// 	node->token = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_external(relative path success)
// t_node	*node_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
// 	node->expanded_args[0] = "ls";
// 	node->expanded_args[1] = "-l";
// 	node->expanded_args[2] = NULL;
// 	node->node_type = COMMAND;
// 	node->cmd_args = "ls -l";
// 	node->redirection_list = NULL;
// 	node->token = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_external(absolute cmd not found)
// t_node	*node_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (1 + 1));
// 	node->expanded_args[0] = "asd/dfa";
// 	node->expanded_args[1] = NULL;
// 	node->node_type = COMMAND;
// 	node->cmd_args = "asd/dfa";
// 	node->redirection_list = NULL;
// 	node->token = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_external(relative cmd not found)
// t_node	*node_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (1 + 1));
// 	node->expanded_args[0] = "dfa";
// 	node->expanded_args[1] = NULL;
// 	node->node_type = COMMAND;
// 	node->cmd_args = "dfa";
// 	node->redirection_list = NULL;
// 	node->token = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// // exec_external(absolute permission denied)
// t_node	*node_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (1 + 1));
// 	node->expanded_args[0] = "/Users/kharuya/test.sh";
// 	node->expanded_args[1] = NULL;
// 	node->node_type = COMMAND;
// 	node->cmd_args = "/Users/kharuya/test.sh";
// 	node->redirection_list = NULL;
// 	node->token = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// }

// // exec_external(execve error)
// t_node	*node_init(void)
// {
// 	t_node	*node;
// 	node = (t_node *)malloc(sizeof(t_node) * 1);
// 	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
// 	node->expanded_args[0] = "ls";
// 	node->expanded_args[1] = "dfa";
// 	node->expanded_args[2] = NULL;
// 	node->node_type = COMMAND;
// 	node->cmd_args = "ls dfa";
// 	node->redirection_list = NULL;
// 	node->token = NULL;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// redirection (normal)
t_abs_node	*node_init(void)
{
	t_abs_node	*node;
	node = (t_abs_node *)malloc(sizeof(t_abs_node) * 1);
	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
	node->expanded_args[0] = "/bin/ls";
	node->expanded_args[1] = "-l";
	node->expanded_args[2] = NULL;
	node->node_type = COMMAND;
	node->cmd_args = "/bin/ls -l";
	node->redirection_list = NULL;
	node->token = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
