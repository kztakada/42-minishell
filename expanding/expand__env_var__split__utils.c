/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__split__utils.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:59:48 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 01:21:47 by katakada         ###   ########.fr       */
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

static t_bool	is_delimiter_for_post_expand_unquoted(char *word)
{
	if (word == NULL)
		return (TRUE);
	if (is_ifs(*word) || *word == '\0' || *word == '*')
		return (TRUE);
	return (FALSE);
}

static char	*use_raw_word_post_expanded(char **raw_str)
{
	char	*raw_str_value;
	int		i;

	i = 0;
	while ((*raw_str)[i] != '\0' && (*raw_str)[i] != '*'
		&& !is_ifs((*raw_str)[i]))
		i++;
	raw_str_value = ft_substr(*raw_str, 0, i);
	if (raw_str_value == NULL)
		return (NULL);
	*raw_str = *raw_str + i;
	return (raw_str_value);
}

t_list	*split_unquoted_word(char **to_expand)
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
