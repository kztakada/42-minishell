/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__split_post_expanded.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 04:10:11 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 01:14:52 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_bool	is_death_dollar_before_quoted(t_list *current_token)
{
	t_expanding_token	*expanding_token;

	if (current_token == NULL)
		return (FALSE);
	expanding_token = (t_expanding_token *)current_token->content;
	if (expanding_token->type == ET_DEATH_DOLLAR)
	{
		if (current_token->next == NULL)
			return (FALSE);
		if (get_ex_token(&(current_token->next))->type == ET_QUOTED_STR)
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

static void	delete_death_dollar_before_quoted(t_list **ex_tokens)
{
	t_list	*to_delete_token;
	t_list	*current_token;

	if (ex_tokens == NULL || *ex_tokens == NULL || (*ex_tokens)->next == NULL)
		return ;
	if (is_death_dollar_before_quoted(*ex_tokens))
	{
		to_delete_token = *ex_tokens;
		*ex_tokens = (*ex_tokens)->next;
		ft_lstdelone(to_delete_token, free_expanding_token);
	}
	if (*ex_tokens == NULL || (*ex_tokens)->next == NULL)
		return ;
	current_token = *ex_tokens;
	while (current_token != NULL && current_token->next != NULL)
	{
		if (is_death_dollar_before_quoted(current_token->next))
		{
			to_delete_token = current_token->next;
			current_token->next = current_token->next->next;
			ft_lstdelone(to_delete_token, free_expanding_token);
		}
		current_token = current_token->next;
	}
}

static t_bool	has_death_dollar_before_1st_separator(t_list *current_token)
{
	t_expanding_token	*expanding_token;

	if (current_token == NULL)
		return (FALSE);
	while (current_token != NULL
		&& get_ex_token(&current_token)->type != ET_SEPARATOR)
	{
		expanding_token = (t_expanding_token *)current_token->content;
		if (expanding_token->type == ET_DEATH_DOLLAR)
			return (TRUE);
		current_token = current_token->next;
	}
	return (FALSE);
}

t_binary_result	split_post_expanded_unquoted_str(t_list **ex_tokens)
{
	t_list			*current_token;
	t_binary_result	result;

	if (ex_tokens == NULL || *ex_tokens == NULL)
		return (SUCCESS_BIN_R);
	delete_prefix_separator(ex_tokens);
	delete_death_dollar_before_quoted(ex_tokens);
	current_token = *ex_tokens;
	while (current_token != NULL)
	{
		if (!has_death_dollar_before_1st_separator(current_token))
		{
			result = split_unquoted_str_before_1st_separator(current_token);
			if (result == FAILURE_BIN_R)
				return (FAILURE_BIN_R);
		}
		to_next_separate_top(&current_token);
	}
	return (SUCCESS_BIN_R);
}
