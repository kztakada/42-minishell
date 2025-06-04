/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__split_post_expanded__utils        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:13:23 by katakada          #+#    #+#             */
/*   Updated: 2025/06/04 23:16:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_binary_result	split_to_expanding_tokens(char *to_split,
		t_list **split_list)
{
	t_list	*under_expanding_token;

	if (*to_split == '\0')
	{
		under_expanding_token = split_unquoted_word(&to_split);
		if (under_expanding_token == NULL)
			return (ft_lstclear(split_list, free_expanding_token),
				FAILURE_BIN_R);
		ft_lstadd_back(split_list, under_expanding_token);
		return (SUCCESS_BIN_R);
	}
	while (*to_split != '\0')
	{
		if (*to_split == '*' || is_ifs(*to_split))
			under_expanding_token = split_operator_word(&to_split);
		else
			under_expanding_token = split_unquoted_word(&to_split);
		if (under_expanding_token == NULL)
			return (ft_lstclear(split_list, free_expanding_token),
				FAILURE_BIN_R);
		ft_lstadd_back(split_list, under_expanding_token);
	}
	return (SUCCESS_BIN_R);
}

static t_binary_result	split_unquoted_str(char *to_split, t_list **first_token)
{
	t_list			*next_token;
	t_list			*split_list;
	t_binary_result	result;

	next_token = (*first_token)->next;
	free((*first_token)->content);
	split_list = NULL;
	result = split_to_expanding_tokens(to_split, &split_list);
	if (result == FAILURE_BIN_R)
		return (FAILURE_BIN_R);
	free(to_split);
	(*first_token)->content = split_list->content;
	(*first_token)->next = split_list->next;
	free(split_list);
	ft_lstadd_back(first_token, next_token);
	*first_token = next_token;
	return (SUCCESS_BIN_R);
}

t_binary_result	split_unquoted_str_before_1st_separator(t_list *current_token)
{
	t_binary_result	result;

	if (current_token == NULL)
		return (SUCCESS_BIN_R);
	while (current_token != NULL
		&& get_ex_token(&current_token)->type != ET_SEPARATOR)
	{
		if (get_ex_token(&current_token)->type == ET_UNQUOTED_STR)
		{
			result = split_unquoted_str(get_ex_token(&current_token)->str,
					&current_token);
			if (result == FAILURE_BIN_R)
				return (FAILURE_BIN_R);
		}
		else
			current_token = current_token->next;
	}
	return (SUCCESS_BIN_R);
}
