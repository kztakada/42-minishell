/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:14:40 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/19 15:15:17 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

t_node	*node_init(void)
{
	t_node	*node;
	node = (t_node *)malloc(sizeof(t_node) * 1);
	node->expanded_args = (char **)malloc(sizeof(char *) * (2 + 1));
	node->expanded_args[0] = "/bin/ls";
	node->expanded_args[1] = "-l";
	node->expanded_args[2] = NULL;
	node->type = N_CMD;
	node->args = "/bin/ls -l";
	node->io_list = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}