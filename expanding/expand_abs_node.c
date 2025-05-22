/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_abs_node.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:40:57 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 23:23:12 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_print.h"

char	**expand_cmd_words(t_list *cmd_words, t_env env)
{
	t_list	*expanding_tokens;
	char	**expanded_str_list;

	expanding_tokens = expand_env_var_with_expanding_tokens(cmd_words, env);
	if (expanding_tokens == NULL)
		return (NULL);
	// print_expanding_token_list(expanding_tokens);
	// if (expand_wildcard(&expanding_tokens) == FAILURE_BIN_R)
	// 	return (NULL);
	expanded_str_list = expanding_tokens_to_arg_list(expanding_tokens);
	ft_lstclear(&expanding_tokens, free_expanding_token);
	if (expanded_str_list == NULL)
		return (NULL);
	return (expanded_str_list);
}

static char	*expand_file_name(t_list *file_name_words, t_env env)
{
	t_list	*expanding_tokens;
	char	**expanded_str_list;
	char	*expanded_file_name;

	expanding_tokens = expand_env_var_with_expanding_tokens(file_name_words,
			env);
	if (expanding_tokens == NULL)
		return (NULL);
	// if (expand_wildcard(&expanding_tokens) == FAILURE_BIN_R)
	// 	return (NULL);
	if (is_ambiguous_redirection(expanding_tokens))
	{
		put_ambiguous_redirection_err(file_name_words);
		return (ft_lstclear(&expanding_tokens, free_expanding_token), NULL);
	}
	expanded_str_list = expanding_tokens_to_arg_list(expanding_tokens);
	ft_lstclear(&expanding_tokens, free_expanding_token);
	if (expanded_str_list == NULL)
		return (NULL);
	expanded_file_name = ft_strdup(expanded_str_list[0]);
	free_str_list(expanded_str_list);
	if (expanded_file_name == NULL)
		return (NULL);
	return (expanded_file_name);
}

t_binary_result	expand_redirections(t_list *redirections, t_env env)
{
	t_list			*current_redirection;
	t_redirection	*redirection;
	char			*expanded_file_name;

	current_redirection = redirections;
	while (current_redirection != NULL)
	{
		redirection = (t_redirection *)current_redirection->content;
		if (redirection->type == RE_OP_HEREDOC)
		{
			current_redirection = current_redirection->next;
			continue ;
		}
		expanded_file_name = expand_file_name(redirection->file_name_words,
				env);
		if (expanded_file_name == NULL)
			return (FAILURE_BIN_R);
		redirection->expanded_file_name = expanded_file_name;
		current_redirection = current_redirection->next;
	}
	return (SUCCESS_BIN_R);
}

static t_bool	has_cmd_words(t_abs_node *abs_node)
{
	t_list	*cmd_words;

	if (abs_node == NULL)
		return (FALSE);
	if (abs_node->cmd_words == NULL)
		return (FALSE);
	cmd_words = abs_node->cmd_words;
	if (cmd_words->content == NULL)
		return (FALSE);
	else
		return (TRUE);
}

t_binary_result	expand_abs_node(t_abs_node *abs_node, t_env env)
{
	char			**expanded_args;
	t_binary_result	e_r_result;

	if (abs_node == NULL)
		return (SUCCESS_BIN_R);
	if (abs_node->type != ABS_COMMAND)
		return (SUCCESS_BIN_R);
	if (has_cmd_words(abs_node))
	{
		expanded_args = expand_cmd_words(abs_node->cmd_words, env);
		if (expanded_args == NULL)
			return (FAILURE_BIN_R);
		abs_node->expanded_args = expanded_args;
		print_str_list(abs_node->expanded_args);
	}
	e_r_result = expand_redirections(abs_node->redirections, env);
	if (e_r_result == FAILURE_BIN_R)
		return (FAILURE_BIN_R);
	print_expanded_file_names(abs_node->redirections);
	return (SUCCESS_BIN_R);
}
