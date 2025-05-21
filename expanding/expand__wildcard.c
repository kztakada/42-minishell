/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:15 by katakada          #+#    #+#             */
/*   Updated: 2025/05/21 04:23:03 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

// t_binary_result	expand_wildcard(t_list **ex_tokens)
// {
// 	t_list			*current_token;
// 	t_binary_result	result;

// 	if (ex_tokens == NULL || *ex_tokens == NULL)
// 		return (SUCCESS_BIN_R);
// 	delete_prefix_separator(ex_tokens);
// 	current_token = *ex_tokens;
// 	while (current_token != NULL)
// 	{
// 		if (has_wildcard_before_1st_separator(current_token))
// 		{
// 			result = expand_wildcard_before_1st_separator(&current_token);
// 			if (result == FAILURE_BIN_R)
// 				return (FAILURE_BIN_R);
// 		}
// 		else
// 			to_next_separate_top(&current_token);
// 	}
// 	return (SUCCESS_BIN_R);
// }
