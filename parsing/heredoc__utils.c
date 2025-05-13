/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:35:21 by katakada          #+#    #+#             */
/*   Updated: 2025/05/13 19:32:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_bool	is_quote_parsed_text(t_parsed_text *parsed_text)
{
	if (parsed_text == NULL)
		return (FALSE);
	if (parsed_text->type == SINGLE_QUOTED
		|| parsed_text->type == DOUBLE_QUOTED)
		return (TRUE);
	return (FALSE);
}

t_bool	has_quoted_text(t_list *parsed_texts)
{
	t_list			*current;
	t_parsed_text	*parsed_text;

	current = parsed_texts;
	while (current)
	{
		parsed_text = (t_parsed_text *)current->content;
		if (is_quote_parsed_text(parsed_text))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

char	*get_heredoc_delimiter(t_list *parsed_texts)
{
	t_list			*current;
	t_parsed_text	*parsed_text;
	char			*expanded_str;

	current = parsed_texts;
	expanded_str = "";
	while (current)
	{
		parsed_text = (t_parsed_text *)current->content;
		expanded_str = ft_strjoin(expanded_str, parsed_text->str);
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
