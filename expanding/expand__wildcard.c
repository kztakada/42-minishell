/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:15 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 20:57:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

t_binary_result	expand_wildcard(t_list **expanding_tokens)
{
	t_list	*current;
	t_list	*expanded_tokens;

	// t_binary_result	result;
	current = *expanding_tokens;
	expanded_tokens = NULL;
	while (current != NULL)
	{
		// if (((t_expanding_token *)current->content)->type == ET_WILDCARD)
		// {
		// 	result = expand_wildcard_to_str_list(current, &expanded_tokens);
		// 	if (result == FAILURE_BIN_R)
		// 		return (FAILURE_BIN_R);
		// }
		// else
		// 	add_back_new_list(current->content, &expanded_tokens, no_del);
		current = current->next;
	}
	// ft_lstclear(expanding_tokens, free_expanding_token);
	*expanding_tokens = expanded_tokens;
	return (SUCCESS_BIN_R);
}
