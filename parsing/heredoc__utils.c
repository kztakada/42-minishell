/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:35:21 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 19:35:58 by katakada         ###   ########.fr       */
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

char	*get_heredoc_delimiter(t_list *file_name_words)
{
	t_list			*current_word;
	t_parsed_word	*file_name_word;
	char			*eof_str;
	char			*tmp;

	current_word = file_name_words;
	eof_str = ft_strdup("");
	if (eof_str == NULL)
		return (perror(ERROR_MALLOC), NULL);
	while (current_word)
	{
		file_name_word = (t_parsed_word *)current_word->content;
		tmp = eof_str;
		eof_str = ft_strjoin(eof_str, file_name_word->str);
		if (eof_str == NULL)
			return (free(tmp), perror(ERROR_MALLOC), NULL);
		free(tmp);
		current_word = current_word->next;
	}
	return (eof_str);
}
