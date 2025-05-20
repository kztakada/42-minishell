/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__expand_plain_word.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:50:46 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 17:37:23 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_list	*expand_operator_word(char **parsed_word_str)
{
	t_list	*under_expanding_token;

	if (parsed_word_str == NULL || *parsed_word_str == NULL)
		return (NULL);
	under_expanding_token = NULL;
	if (**parsed_word_str == '*')
	{
		under_expanding_token = init_expanding_token(ET_WILDCARD);
		(*parsed_word_str)++;
	}
	else if (is_ifs(**parsed_word_str))
	{
		under_expanding_token = init_expanding_token(ET_SEPARATOR);
		while (is_ifs(**parsed_word_str))
			(*parsed_word_str)++;
	}
	if (under_expanding_token == NULL)
		return (NULL);
	return (under_expanding_token);
}

static t_list	*expand_death_dollar_word(char **parsed_word_str)
{
	t_list	*under_expanding_token;

	under_expanding_token = init_expanding_token(ET_DEATH_DOLLAR);
	(*parsed_word_str)++;
	if (under_expanding_token == NULL)
		return (NULL);
	return (under_expanding_token);
}

static t_bool	is_delimiter_for_unquoted(char *word)
{
	if (word == NULL)
		return (TRUE);
	if (is_ifs(*word) || *word == '\0' || *word == '*' || is_death_dollar(word))
		return (TRUE);
	return (FALSE);
}

static t_list	*expand_unquoted_word(char **to_expand, t_env env)
{
	char				*unquoted_str;
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	unquoted_str = strdup("");
	if (unquoted_str == NULL)
		return (NULL);
	while (!is_delimiter_for_unquoted(*to_expand))
	{
		if (**to_expand == '$')
			unquoted_str = strjoin_free(unquoted_str, expand_dollar(to_expand,
						env));
		else
			unquoted_str = strjoin_free(unquoted_str,
					expand_normal_str(to_expand));
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

t_list	*expand_plain_word(t_list *current_words, t_env env)
{
	t_list	*expanded_tokens;
	t_list	*under_expanding_token;
	char	*parsed_word_str;

	parsed_word_str = ((t_parsed_word *)current_words->content)->str;
	if (parsed_word_str == NULL)
		return (NULL);
	expanded_tokens = NULL;
	while (*parsed_word_str != '\0')
	{
		if (*parsed_word_str == '*' || is_ifs(*parsed_word_str))
			under_expanding_token = expand_operator_word(&parsed_word_str);
		else if (is_death_dollar(parsed_word_str))
			under_expanding_token = expand_death_dollar_word(&parsed_word_str);
		else
			under_expanding_token = expand_unquoted_word(&parsed_word_str, env);
		if (under_expanding_token == NULL)
			return (ft_lstclear(&expanded_tokens, free_expanding_token), NULL);
		ft_lstadd_back(&expanded_tokens, under_expanding_token);
	}
	return (expanded_tokens);
}
