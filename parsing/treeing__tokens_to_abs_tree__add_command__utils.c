/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__tokens_to_abs_tree__add_command__u        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 22:34:14 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 17:52:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_binary_result	append_quoted_to_parsed_words(t_list **current_tokens,
		t_list **parsed_words)
{
	t_parsed_word	*parsed_word;

	parsed_word = (t_parsed_word *)malloc(sizeof(t_parsed_word));
	if (parsed_word == NULL)
		return (FAILURE_BIN_R);
	if (get_token(*current_tokens)->type == QUOTE_SINGLE)
		parsed_word->type = W_SINGLE_QUOTED;
	else
		parsed_word->type = W_DOUBLE_QUOTED;
	forward_token_list(current_tokens);
	parsed_word->str = ft_strdup(get_token(*current_tokens)->value);
	if (parsed_word->str == NULL)
	{
		free(parsed_word);
		return (FAILURE_BIN_R);
	}
	forward_token_list(current_tokens);
	forward_token_list(current_tokens);
	return (add_back_new_list((void *)parsed_word, parsed_words,
			free_parsed_word));
}

t_binary_result	append_plain_word_to_parsed_words(t_list **current_tokens,
		t_list **parsed_words)
{
	t_parsed_word	*parsed_word;

	parsed_word = (t_parsed_word *)malloc(sizeof(t_parsed_word));
	if (parsed_word == NULL)
		return (FAILURE_BIN_R);
	parsed_word->type = W_PLAIN;
	parsed_word->str = ft_strdup(get_token(*current_tokens)->value);
	if (parsed_word->str == NULL)
	{
		free(parsed_word);
		return (FAILURE_BIN_R);
	}
	forward_token_list(current_tokens);
	return (add_back_new_list((void *)parsed_word, parsed_words,
			free_parsed_word));
}

static t_binary_result	avoid_parsed_word_from_token(t_list **current_tokens,
		char *dup_str, int i)
{
	char	*tmp;

	if (dup_str[i] == '\0')
		forward_token_list(current_tokens);
	else
	{
		dup_str = dup_str + i;
		tmp = ft_strdup(dup_str);
		if (tmp == NULL)
			return (FAILURE_BIN_R);
		free(get_token(*current_tokens)->value);
		get_token(*current_tokens)->value = tmp;
	}
	return (SUCCESS_BIN_R);
}

t_binary_result	append_only1st_word_to_parsed_words(t_list **current_tokens,
		t_list **parsed_words)
{
	t_parsed_word	*parsed_word;
	char			*dup_str;
	int				i;

	parsed_word = (t_parsed_word *)malloc(sizeof(t_parsed_word));
	if (parsed_word == NULL)
		return (FAILURE_BIN_R);
	parsed_word->type = W_PLAIN;
	dup_str = get_token(*current_tokens)->value;
	while (is_ifs(dup_str[0]))
		dup_str++;
	i = 0;
	while (dup_str[i] && !is_ifs(dup_str[i]))
		i++;
	parsed_word->str = ft_substr(dup_str, 0, i);
	if (parsed_word->str == NULL)
		return (free(parsed_word), FAILURE_BIN_R);
	if (avoid_parsed_word_from_token(current_tokens, dup_str,
			i) == FAILURE_BIN_R)
		return (free(parsed_word), FAILURE_BIN_R);
	return (add_back_new_list((void *)parsed_word, parsed_words,
			free_parsed_word));
}

t_binary_result	append_chainwords_to_file_name_words(t_list **current_tokens,
		t_token *end_token, t_list **file_name_words)
{
	t_binary_result	result;

	result = SUCCESS_BIN_R;
	while (get_token(*current_tokens)->id < end_token->id
		&& result == SUCCESS_BIN_R)
	{
		if (is_in(QUOTE_DICT, get_token(*current_tokens)))
			result = append_quoted_to_parsed_words(current_tokens,
					file_name_words);
		else if (is_ifs(get_token(*current_tokens)->value[0]))
			break ;
		else if (has_ifs(get_token(*current_tokens)->value))
		{
			result = append_only1st_word_to_parsed_words(current_tokens,
					file_name_words);
			break ;
		}
		else
			result = append_plain_word_to_parsed_words(current_tokens,
					file_name_words);
	}
	if (result == FAILURE_BIN_R)
		return (ft_lstclear(file_name_words, free_parsed_word), FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}
