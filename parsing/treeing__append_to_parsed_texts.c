/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__append_to_parsed_texts.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:36:32 by katakada          #+#    #+#             */
/*   Updated: 2025/05/11 19:33:11 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_binary_result	append_quoted_to_parsed_texts(t_list **current_tokens,
		t_list **parsed_texts)
{
	t_parsed_text	*parsed_text;

	parsed_text = (t_parsed_text *)malloc(sizeof(t_parsed_text));
	if (parsed_text == NULL)
		return (FAILURE_BIN_R);
	if (get_token(*current_tokens)->type == QUOTE_SINGLE)
		parsed_text->type = SINGLE_QUOTED;
	else
		parsed_text->type = DOUBLE_QUOTED;
	forward_token_list(current_tokens);
	parsed_text->str = strdup(get_token(*current_tokens)->value);
	if (parsed_text->str == NULL)
	{
		free(parsed_text);
		return (FAILURE_BIN_R);
	}
	forward_token_list(current_tokens);
	forward_token_list(current_tokens);
	return (add_back_new_list((void *)parsed_text, parsed_texts,
			free_parsed_text));
}

t_binary_result	append_plain_text_to_parsed_texts(t_list **current_tokens,
		t_list **parsed_texts)
{
	t_parsed_text	*parsed_text;

	parsed_text = (t_parsed_text *)malloc(sizeof(t_parsed_text));
	if (parsed_text == NULL)
		return (FAILURE_BIN_R);
	parsed_text->type = PLAIN_TEXT;
	parsed_text->str = strdup(get_token(*current_tokens)->value);
	if (parsed_text->str == NULL)
	{
		free(parsed_text);
		return (FAILURE_BIN_R);
	}
	forward_token_list(current_tokens);
	return (add_back_new_list((void *)parsed_text, parsed_texts,
			free_parsed_text));
}

static t_binary_result	avoid_parsed_text_from_token(t_list **current_tokens,
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

t_binary_result	append_only1st_text_to_parsed_texts(t_list **current_tokens,
		t_list **parsed_texts)
{
	t_parsed_text	*parsed_text;
	char			*dup_str;
	int				i;

	parsed_text = (t_parsed_text *)malloc(sizeof(t_parsed_text));
	if (parsed_text == NULL)
		return (FAILURE_BIN_R);
	parsed_text->type = PLAIN_TEXT;
	dup_str = get_token(*current_tokens)->value;
	while (is_ifs(dup_str[0]))
		dup_str++;
	i = 0;
	while (dup_str[i] && !is_ifs(dup_str[i]))
		i++;
	parsed_text->str = ft_substr(dup_str, 0, i);
	if (parsed_text->str == NULL)
		return (free(parsed_text), FAILURE_BIN_R);
	if (avoid_parsed_text_from_token(current_tokens, dup_str,
			i) == FAILURE_BIN_R)
		return (free(parsed_text), FAILURE_BIN_R);
	return (add_back_new_list((void *)parsed_text, parsed_texts,
			free_parsed_text));
}

t_binary_result	append_chaintexts_to_file_name(t_list **current_tokens,
		t_token *end_token, t_list **file_name)
{
	t_binary_result	result;

	result = SUCCESS_BIN_R;
	while (get_token(*current_tokens)->id < end_token->id
		&& result == SUCCESS_BIN_R)
	{
		if (is_in(QUOTE_DICT, get_token(*current_tokens)))
			result = append_quoted_to_parsed_texts(current_tokens, file_name);
		else if (is_ifs(get_token(*current_tokens)->value[0]))
			break ;
		else if (has_ifs(get_token(*current_tokens)->value))
		{
			result = append_only1st_text_to_parsed_texts(current_tokens,
					file_name);
			break ;
		}
		else
			result = append_plain_text_to_parsed_texts(current_tokens,
					file_name);
	}
	if (result == FAILURE_BIN_R)
		return (ft_lstclear(file_name, free_parsed_text), FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}
