/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:18:10 by katakada          #+#    #+#             */
/*   Updated: 2025/05/12 20:00:33 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

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

// t_abs_node	*get_abs_node(t_abs_node **abs_tree)
// {
// 	if (*abs_tree == NULL)
// 		return (NULL);
// 	return (*abs_tree);
// }

t_abs_node	*get_working_node(t_parsing_state *parsing_state)
{
	if (parsing_state->working_node == NULL)
		return (NULL);
	return (*(parsing_state->working_node));
}

t_abs_node	*get_tree_top_node(t_parsing_state *parsing_state)
{
	if (parsing_state->tree_top_node == NULL)
		return (NULL);
	return (*(parsing_state->tree_top_node));
}