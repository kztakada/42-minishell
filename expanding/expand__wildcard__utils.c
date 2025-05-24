/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard__utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 01:57:45 by katakada          #+#    #+#             */
/*   Updated: 2025/05/25 03:11:07 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_list	*free_and_get_next_separator(t_list *current_token)
{
	t_list	*next_token;

	if (current_token == NULL)
		return (NULL);
	while (current_token != NULL
		&& get_ex_token(&current_token)->type != ET_SEPARATOR)
	{
		next_token = current_token->next;
		ft_lstdelone(current_token, free_expanding_token);
		current_token = next_token;
	}
	return (next_token);
}

void	reconect_wild_expanded_list(t_list *wildcard_in_tokens,
		t_list *wild_expanded_tokens)
{
	t_list	*next_block_token;

	next_block_token = free_and_get_next_separator(wildcard_in_tokens->next);
	wildcard_in_tokens->content = wild_expanded_tokens->content;
	wildcard_in_tokens->next = wild_expanded_tokens->next;
	ft_lstlast(wild_expanded_tokens)->next = next_block_token;
	free(wild_expanded_tokens);
}

t_bool	has_wildcard_before_1st_separator(t_list *current_token)
{
	t_expanding_token	*expanding_token;

	if (current_token == NULL)
		return (FALSE);
	while (current_token != NULL
		&& get_ex_token(&current_token)->type != ET_SEPARATOR)
	{
		expanding_token = (t_expanding_token *)current_token->content;
		if (expanding_token->type == ET_WILDCARD)
			return (TRUE);
		else
			current_token = current_token->next;
	}
	return (FALSE);
}

t_binary_result	insert_separator_to_quoted_ex_tokens(t_list *ex_tokens)
{
	t_list				*current_token;
	t_expanding_token	*expanding_token;
	t_list				*new_separator;
	t_list				*tmp;

	if (ex_tokens == NULL)
		return (SUCCESS_BIN_R);
	current_token = ex_tokens;
	while (current_token != NULL)
	{
		expanding_token = (t_expanding_token *)current_token->content;
		if (expanding_token->type == ET_QUOTED_STR
			&& current_token->next != NULL)
		{
			new_separator = init_expanding_token(ET_SEPARATOR);
			if (new_separator == NULL)
				return (FAILURE_BIN_R);
			tmp = current_token->next;
			current_token->next = new_separator;
			new_separator->next = tmp;
		}
		current_token = current_token->next;
	}
	return (SUCCESS_BIN_R);
}
