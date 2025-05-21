/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__split_post_expanded.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 04:10:11 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 00:49:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

void	delete_prefix_separator(t_list **ex_tokens)
{
	t_list	*to_delete_token;

	if (ex_tokens == NULL)
		return ;
	while (*ex_tokens != NULL && get_ex_token(ex_tokens)->type == ET_SEPARATOR)
	{
		to_delete_token = *ex_tokens;
		*ex_tokens = (*ex_tokens)->next;
		ft_lstdelone(to_delete_token, free_expanding_token);
	}
}

t_bool	is_death_dollar_before_quoted(t_list *current_token)
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

void	delete_death_dollar_before_quoted(t_list **ex_tokens)
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

t_bool	has_death_dollar_before_1st_separator(t_list *current_token)
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

void	to_next_separate_top(t_list **current_token)
{
	t_expanding_token	*expanding_token;

	if (current_token == NULL || *current_token == NULL)
		return ;
	while (*current_token != NULL)
	{
		expanding_token = (t_expanding_token *)(*current_token)->content;
		*current_token = (*current_token)->next;
		if (expanding_token->type == ET_SEPARATOR)
			break ;
	}
}

t_bool	is_delimiter_for_post_expand_unquoted(char *word)
{
	if (word == NULL)
		return (TRUE);
	if (is_ifs(*word) || *word == '\0' || *word == '*')
		return (TRUE);
	return (FALSE);
}

t_bool	can_use_raw_cahr_post_expanded(char c)
{
	if (c == '\0' || c == '*' || is_ifs(c))
		return (FALSE);
	return (TRUE);
}

static char	*use_raw_word_post_expanded(char **raw_str)
{
	char	*raw_str_value;
	int		i;

	i = 0;
	while (can_use_raw_cahr_post_expanded((*raw_str)[i]))
		i++;
	raw_str_value = ft_substr(*raw_str, 0, i);
	if (raw_str_value == NULL)
		return (NULL);
	*raw_str = *raw_str + i;
	return (raw_str_value);
}

static t_list	*split_unquoted_word(char **to_expand)
{
	char				*unquoted_str;
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	unquoted_str = ft_strdup("");
	if (unquoted_str == NULL)
		return (NULL);
	while (!is_delimiter_for_post_expand_unquoted(*to_expand))
	{
		unquoted_str = strjoin_free(unquoted_str,
				use_raw_word_post_expanded(to_expand));
		if (unquoted_str == NULL)
			return (ft_lstclear(&expanded_token, free_expanding_token), NULL);
	}
	expanded_token = init_expanding_token(ET_UNQUOTED_STR);
	if (expanded_token == NULL)
		return (free(unquoted_str), ft_lstclear(&expanded_token,
				free_expanding_token), NULL);
	expanding_token = (t_expanding_token *)expanded_token->content;
	expanding_token->str = unquoted_str;
	return (expanded_token);
}

t_binary_result	split_to_expanding_tokens(char *to_split, t_list **split_list)
{
	t_list	*under_expanding_token;

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

t_binary_result	split_unquoted_str(char *to_split, t_list **first_token)
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
