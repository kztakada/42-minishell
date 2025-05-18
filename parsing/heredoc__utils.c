/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:35:21 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:27:22 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static t_bool	is_quote_parsed_word(t_parsed_word *parsed_word)
{
	if (parsed_word == NULL)
		return (FALSE);
	if (parsed_word->type == W_SINGLE_QUOTED
		|| parsed_word->type == W_DOUBLE_QUOTED)
		return (TRUE);
	return (FALSE);
}

t_bool	has_quoted_text(t_list *parsed_words)
{
	t_list			*current;
	t_parsed_word	*parsed_word;

	current = parsed_words;
	while (current)
	{
		parsed_word = (t_parsed_word *)current->content;
		if (is_quote_parsed_word(parsed_word))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

char	*get_heredoc_delimiter(t_list *parsed_words)
{
	t_list			*current;
	t_parsed_word	*parsed_word;
	char			*expanded_str;

	current = parsed_words;
	expanded_str = "";
	while (current)
	{
		parsed_word = (t_parsed_word *)current->content;
		expanded_str = ft_strjoin(expanded_str, parsed_word->str);
		current = current->next;
	}
	return (expanded_str);
}

char	*e_handle_strjoin_free(char *s1, char *s2)
{
	char	*result;
	t_bool	can_free_s1;
	t_bool	can_free_s2;

	can_free_s1 = TRUE;
	can_free_s2 = TRUE;
	if (s1 == NULL)
	{
		s1 = "";
		can_free_s1 = FALSE;
	}
	if (s2 == NULL)
	{
		s2 = "";
		can_free_s2 = FALSE;
	}
	result = ft_strjoin(s1, s2);
	if (result == NULL)
		return (exit(EXIT_FAILURE), NULL);
	if (can_free_s1 == TRUE)
		free(s1);
	if (can_free_s2 == TRUE)
		free(s2);
	return (result);
}

char	*e_handle_substr(char *to_expand, int len)
{
	char	*tmp;

	tmp = ft_substr(to_expand, 0, len);
	if (tmp == NULL)
		return (exit(EXIT_FAILURE), NULL);
	return (tmp);
}
