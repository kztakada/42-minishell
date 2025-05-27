/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard__extract_tokens_for_wildca        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:31:00 by katakada          #+#    #+#             */
/*   Updated: 2025/05/27 20:31:20 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

t_binary_result	delete_prefix_adrr(t_list **for_check, t_bool *has_prefix_addr)
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
	else if (ft_strlen(get_ex_token(for_check)->str) > 2
		&& get_ex_token(for_check)->str[0] == '.'
		&& get_ex_token(for_check)->str[1] == '/')
	{
		tmp_str = get_ex_token(for_check)->str;
		get_ex_token(for_check)->str = ft_strdup(tmp_str + 2);
		*has_prefix_addr = TRUE;
		if (get_ex_token(for_check)->str == NULL)
			return (perror(ERROR_MALLOC), free(tmp_str), FAILURE_BIN_R);
	}
	return (SUCCESS_BIN_R);
}

t_binary_result	delete_suffix_adrr(t_list *for_check, t_bool *has_suffix_addr)
{
	t_list	*origin;

	*has_suffix_addr = FALSE;
	origin = for_check;
	if (for_check == NULL)
		return (SUCCESS_BIN_R);
	for_check = ft_lstlast(for_check);
	if ((get_ex_token(&for_check)->type != ET_UNQUOTED_STR
			&& get_ex_token(&for_check)->type != ET_QUOTED_STR))
		return (SUCCESS_BIN_R);
	if (ft_strcmp(get_ex_token(&for_check)->str, "/") == 0)
	{
		delete_last_ex_token(origin);
		*has_suffix_addr = TRUE;
	}
	else if (ft_strlen(get_ex_token(&for_check)->str) > 1
		&& get_ex_token(&for_check)->str[ft_strlen(get_ex_token(&for_check)->str)
		- 1] == '/')
	{
		get_ex_token(&for_check)->str[ft_strlen(get_ex_token(&for_check)->str)
			- 1] = '\0';
		*has_suffix_addr = TRUE;
	}
	return (SUCCESS_BIN_R);
}

t_list	*extract_tokens_for_wildcard_check(t_list *with_wildcd,
		t_bool *has_prefix_addr, t_bool *has_suffix_addr)
{
	t_list	*for_check;
	t_list	*new_token;
	char	*new_str;

	if (with_wildcd == NULL)
		return (NULL);
	for_check = NULL;
	new_str = ft_strdup("");
	if (new_str == NULL)
		return (perror(ERROR_MALLOC), NULL);
	while (with_wildcd != NULL
		&& get_ex_token(&with_wildcd)->type != ET_SEPARATOR)
	{
		if (get_ex_token(&with_wildcd)->type == ET_WILDCARD)
		{
			if (ft_strcmp(new_str, "") != 0)
			{
				new_token = expand_single_quoted_word(new_str);
				if (new_token == NULL)
					return (ft_lstclear(&for_check, free_expanding_token),
						free(new_str), NULL);
				ft_lstadd_back(&for_check, new_token);
				free(new_str);
				new_str = ft_strdup("");
				if (new_str == NULL)
					return (ft_lstclear(&for_check, free_expanding_token),
						NULL);
			}
			new_token = init_expanding_token(ET_WILDCARD);
			if (new_token == NULL)
				return (ft_lstclear(&for_check, free_expanding_token),
					free(new_str), NULL);
			ft_lstadd_back(&for_check, new_token);
			while (get_ex_token(&with_wildcd)->type != ET_WILDCARD)
				forward_token_list(&with_wildcd);
		}
		else if (get_ex_token(&with_wildcd)->type == ET_UNQUOTED_STR
			|| get_ex_token(&with_wildcd)->type == ET_QUOTED_STR
			|| get_ex_token(&with_wildcd)->type == ET_DEATH_DOLLAR)
			new_str = strjoin_free(new_str,
					ft_strdup(get_ex_token(&with_wildcd)->str));
		forward_token_list(&with_wildcd);
	}
	if (ft_strcmp(new_str, "") != 0)
	{
		new_token = expand_single_quoted_word(new_str);
		if (new_token == NULL)
			return (ft_lstclear(&for_check, free_expanding_token),
				free(new_str), NULL);
		ft_lstadd_back(&for_check, new_token);
	}
	free(new_str);
	if (delete_prefix_adrr(&for_check, has_prefix_addr) == FAILURE_BIN_R)
		return (ft_lstclear(&for_check, free_expanding_token), NULL);
	if (delete_suffix_adrr(for_check, has_suffix_addr) == FAILURE_BIN_R)
		return (ft_lstclear(&for_check, free_expanding_token), NULL);
	return (for_check);
}
