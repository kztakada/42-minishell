/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:18:10 by katakada          #+#    #+#             */
/*   Updated: 2025/05/16 11:53:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_abs_node	*init_abs_node(t_abs_node_type abs_node_type)
{
	t_abs_node	*abs_node;

	abs_node = (t_abs_node *)malloc(sizeof(t_abs_node));
	if (abs_node == NULL)
		return (NULL);
	abs_node->is_subshell = FALSE;
	abs_node->type = abs_node_type;
	abs_node->command_args = NULL;
	abs_node->expanded_args = NULL;
	abs_node->redirection_list = NULL;
	abs_node->left = NULL;
	abs_node->right = NULL;
	return (abs_node);
}

t_binary_result	add_back_new_list(void *content, t_list **existing_list,
		void (*del)(void *))
{
	t_list	*new_list;

	new_list = ft_lstnew(content);
	if (new_list == NULL)
	{
		if (del != NULL)
			ft_lstclear(existing_list, del);
		return (FAILURE_BIN_R);
	}
	if (*existing_list == NULL)
		*existing_list = new_list;
	else
		ft_lstadd_back(existing_list, new_list);
	return (SUCCESS_BIN_R);
}

void	free_parsed_text(void *content)
{
	t_parsed_text	*parsed_text;

	parsed_text = (t_parsed_text *)content;
	if (parsed_text->str != NULL)
		free(parsed_text->str);
	free(parsed_text);
}

void	free_redirection(void *content)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)content;
	if (redirection->expanded_file_name != NULL)
		free(redirection->expanded_file_name);
	if (redirection->file_name != NULL)
		ft_lstclear(&(redirection->file_name), free_parsed_text);
	free(redirection);
}
