/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard__extract_tokens_for_wildca        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:31:00 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 22:45:10 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_binary_result	delete_prefix_adrr(t_list **for_check,
		t_bool *has_prefix_addr)
{
	t_list	*tmp_list;
	char	*tmp_str;

	*has_prefix_addr = FALSE;
	if (for_check == NULL || *for_check == NULL)
		return (SUCCESS_BIN_R);
	if ((get_ex_token(for_check)->type != ET_UNQUOTED_STR
			&& get_ex_token(for_check)->type != ET_QUOTED_STR))
		return (SUCCESS_BIN_R);
	if (ft_strcmp(get_ex_token(for_check)->str, "./") == 0)
	{
		tmp_list = *for_check;
		*for_check = (*for_check)->next;
		ft_lstdelone(tmp_list, free_expanding_token);
		*has_prefix_addr = TRUE;
	}
	else if (ft_strncmp(get_ex_token(for_check)->str, "./", 2) == 0)
	{
		tmp_str = get_ex_token(for_check)->str;
		get_ex_token(for_check)->str = ft_strdup(tmp_str + 2);
		*has_prefix_addr = TRUE;
		if (get_ex_token(for_check)->str == NULL)
			return (perror(ERROR_MALLOC), free(tmp_str), FAILURE_BIN_R);
	}
	return (SUCCESS_BIN_R);
}

static t_binary_result	delete_suffix_adrr(t_list *for_check,
		t_bool *has_suffix_addr)
{
	t_list	*origin;
	int		end_i;

	*has_suffix_addr = FALSE;
	origin = for_check;
	if (for_check == NULL)
		return (SUCCESS_BIN_R);
	for_check = ft_lstlast(for_check);
	if ((get_ex_token(&for_check)->type != ET_UNQUOTED_STR
			&& get_ex_token(&for_check)->type != ET_QUOTED_STR))
		return (SUCCESS_BIN_R);
	end_i = ft_strlen(get_ex_token(&for_check)->str) - 1;
	if (ft_strcmp(get_ex_token(&for_check)->str, "/") == 0)
	{
		delete_last_ex_token(origin);
		*has_suffix_addr = TRUE;
	}
	else if (ft_strlen(get_ex_token(&for_check)->str) > 1
		&& get_ex_token(&for_check)->str[end_i] == '/')
	{
		get_ex_token(&for_check)->str[end_i] = '\0';
		*has_suffix_addr = TRUE;
	}
	return (SUCCESS_BIN_R);
}

static t_binary_result	make_new_str_token(t_list **for_check, char **new_str)
{
	t_list	*new_token;

	if (ft_strcmp(*new_str, "") != 0)
	{
		new_token = expand_single_quoted_word(*new_str);
		if (new_token == NULL)
			return (free(*new_str), FAILURE_BIN_R);
		ft_lstadd_back(for_check, new_token);
		free(*new_str);
		*new_str = ft_strdup("");
		if (*new_str == NULL)
			return (perror(ERROR_MALLOC), FAILURE_BIN_R);
	}
	return (SUCCESS_BIN_R);
}

static t_binary_result	extract_tokens_core(t_list *with_wildcd,
		t_list **for_check, char **new_str)
{
	t_list	*new_token;

	while (with_wildcd != NULL
		&& get_ex_token(&with_wildcd)->type != ET_SEPARATOR)
	{
		if (get_ex_token(&with_wildcd)->type == ET_WILDCARD)
		{
			if (make_new_str_token(for_check, new_str) == FAILURE_BIN_R)
				return (FAILURE_BIN_R);
			new_token = init_expanding_token(ET_WILDCARD);
			if (new_token == NULL)
				return (FAILURE_BIN_R);
			ft_lstadd_back(for_check, new_token);
			while (get_ex_token(&with_wildcd)->type != ET_WILDCARD)
				forward_token_list(&with_wildcd);
		}
		else if (is_str_ex_token_type(get_ex_token(&with_wildcd)))
			*new_str = strjoin_free(*new_str,
					ft_strdup(get_ex_token(&with_wildcd)->str));
		forward_token_list(&with_wildcd);
	}
	if (make_new_str_token(for_check, new_str) == FAILURE_BIN_R)
		return (FAILURE_BIN_R);
	return (SUCCESS_BIN_R);
}

t_list	*extract_tokens_for_wildcard_check(t_list *with_wildcd,
		t_bool *has_prefix_addr, t_bool *has_suffix_addr)
{
	t_list	*for_check;
	char	*new_str;

	if (with_wildcd == NULL)
		return (NULL);
	for_check = NULL;
	new_str = ft_strdup("");
	if (new_str == NULL)
		return (perror(ERROR_MALLOC), NULL);
	if (extract_tokens_core(with_wildcd, &for_check, &new_str) == FAILURE_BIN_R)
		return (free(new_str), ft_lstclear(&for_check, free_expanding_token),
			NULL);
	free(new_str);
	if (delete_prefix_adrr(&for_check, has_prefix_addr) == FAILURE_BIN_R)
		return (ft_lstclear(&for_check, free_expanding_token), NULL);
	if (delete_suffix_adrr(for_check, has_suffix_addr) == FAILURE_BIN_R)
		return (ft_lstclear(&for_check, free_expanding_token), NULL);
	return (for_check);
}
