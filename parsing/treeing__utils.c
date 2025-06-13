/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:18:10 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 22:55:40 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_abs_node	*init_abs_node(t_abs_node_type abs_node_type)
{
	t_abs_node	*abs_node;

	abs_node = (t_abs_node *)malloc(sizeof(t_abs_node));
	if (abs_node == NULL)
		return (perror(ERROR_MALLOC), NULL);
	abs_node->type = abs_node_type;
	abs_node->cmd_words = NULL;
	abs_node->expanded_args = NULL;
	abs_node->redirections = NULL;
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
		return (perror(ERROR_MALLOC), FAILURE_BIN_R);
	}
	if (*existing_list == NULL)
		*existing_list = new_list;
	else
		ft_lstadd_back(existing_list, new_list);
	return (SUCCESS_BIN_R);
}

void	free_parsed_word(void *content)
{
	t_parsed_word	*parsed_word;

	parsed_word = (t_parsed_word *)content;
	if (parsed_word->str != NULL)
		free(parsed_word->str);
	free(parsed_word);
}

void	free_redirection(void *content)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)content;
	if (redirection->expanded_file_name != NULL)
		free(redirection->expanded_file_name);
	if (redirection->file_name_words != NULL)
		ft_lstclear(&(redirection->file_name_words), free_parsed_word);
	free(redirection);
}
