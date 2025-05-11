/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeing__add_content_to_working_abs_node.c         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:44:53 by katakada          #+#    #+#             */
/*   Updated: 2025/05/11 20:42:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_binary_result	set_file_name_to_redirection(t_list **current_tokens,
		t_token *end_token, t_redirection *redirection)
{
	t_binary_result	result;

	if (is_ifs(get_token(*current_tokens)->value[0]))
	{
		result = append_only1st_text_to_parsed_texts(current_tokens,
				&redirection->file_name);
		if (result == FAILURE_BIN_R)
			return (FAILURE_BIN_R);
		if (get_token(*current_tokens)->id >= end_token->id
			|| is_ifs(get_token(*current_tokens)->value[0]))
			return (SUCCESS_BIN_R);
	}
	result = append_chaintexts_to_file_name(current_tokens, end_token,
			&redirection->file_name);
	if (result == FAILURE_BIN_R)
		return (ft_lstclear(&(redirection->file_name), free_parsed_text),
			FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}

static t_redirection	*init_redirection(t_token_type token_type)
{
	t_redirection	*redirection;

	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	redirection->fd = 0;
	redirection->expanded_file_name = NULL;
	redirection->file_name = NULL;
	if (token_type == OP_HEREDOC)
		redirection->type = RE_OP_HEREDOC;
	else if (token_type == OP_INPUT)
		redirection->type = RE_OP_INPUT;
	else if (token_type == OP_OUTPUT)
		redirection->type = RE_OP_OUTPUT;
	else if (token_type == OP_APPEND)
		redirection->type = RE_OP_APPEND;
	else
	{
		free(redirection);
		return (NULL);
	}
	return (redirection);
}

static t_binary_result	add_redirection_to_working_abs_node(t_list **current_tokens,
		t_token *end_token, t_parsing_state *parsing_state)
{
	t_redirection	*redirection;
	t_binary_result	result;

	redirection = init_redirection(get_token(*current_tokens)->type);
	if (redirection == NULL)
		return (FAILURE_BIN_R);
	forward_token_list(current_tokens);
	result = set_file_name_to_redirection(current_tokens, end_token,
			redirection);
	if (result == SUCCESS_BIN_R)
		result = add_back_new_list((void *)redirection,
				&parsing_state->working_node->redirection_list,
				free_redirection);
	if (redirection->type == RE_OP_HEREDOC)
		result = add_back_new_list((void *)redirection,
				&parsing_state->heredoc_list, free_redirection);
	if (result == FAILURE_BIN_R)
		free_redirection(redirection);
	return (result);
}

static t_binary_result	add_command_args_to_working_abs_node(t_list **current_tokens,
		t_token *end_token, t_parsing_state *parsing_state)
{
	t_binary_result	result;

	result = SUCCESS_BIN_R;
	while (get_token(*current_tokens)->id < end_token->id
		&& result == SUCCESS_BIN_R)
	{
		if (is_in(REDIRECT_OP, get_token(*current_tokens)))
			break ;
		else if (is_in(QUOTE_DICT, get_token(*current_tokens)))
			result = append_quoted_to_parsed_texts(current_tokens,
					&(parsing_state->working_node->command_args));
		else
			result = append_plain_text_to_parsed_texts(current_tokens,
					&(parsing_state->working_node->command_args));
	}
	if (result == FAILURE_BIN_R)
		return (ft_lstclear(&parsing_state->working_node->command_args,
				free_parsed_text), FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}

t_binary_result	add_content_to_working_abs_node(t_list *tokens_begin,
		t_list *tokens_end, t_parsing_state *parsing_state)
{
	t_list			*current_tokens;
	t_token			*end_token;
	t_binary_result	parse_result;

	current_tokens = tokens_begin;
	end_token = get_token(tokens_end);
	parse_result = SUCCESS_BIN_R;
	while (get_token(current_tokens)->id < end_token->id
		&& parse_result == SUCCESS_BIN_R)
	{
		if (is_in(REDIRECT_OP, get_token(current_tokens)))
			parse_result = add_redirection_to_working_abs_node(&current_tokens,
					end_token, parsing_state);
		else
			parse_result = add_command_args_to_working_abs_node(&current_tokens,
					end_token, parsing_state);
	}
	return (parse_result);
}
