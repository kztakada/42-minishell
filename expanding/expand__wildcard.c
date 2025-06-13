/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:15 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 23:10:09 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

t_list	*make_d_name_ex_token(char *d_name, t_bool has_prefix_addr,
		t_bool has_suffix_addr)
{
	char	*d_name_copy;
	t_list	*d_name_ex_token;

	d_name_copy = ft_strdup("");
	if (has_prefix_addr == TRUE)
		d_name_copy = strjoin_free(ft_strdup("./"), d_name_copy);
	d_name_copy = strjoin_free(d_name_copy, ft_strdup(d_name));
	if (has_suffix_addr == TRUE)
		d_name_copy = strjoin_free(d_name_copy, ft_strdup("/"));
	if (d_name_copy == NULL)
		return (perror(ERROR_MALLOC), NULL);
	d_name_ex_token = expand_single_quoted_word(d_name_copy);
	free(d_name_copy);
	if (d_name_ex_token == NULL)
		return (NULL);
	return (d_name_ex_token);
}

t_binary_result	retrieve_d_names_to_replace(DIR *dir, t_list *with_wildcd,
		t_list **replaced_d_names)
{
	struct dirent	*entry;
	t_list			*d_name_ex_token;
	t_list			*for_check;
	t_bool			has_prefix_addr;
	t_bool			has_suffix_addr;

	for_check = extract_tokens_for_wildcard_check(with_wildcd, &has_prefix_addr,
			&has_suffix_addr);
	if (for_check == NULL)
		return (perror(ERROR_MALLOC), FAILURE_BIN_R);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (can_replace_wildcard(entry, for_check, has_suffix_addr))
		{
			d_name_ex_token = make_d_name_ex_token(entry->d_name,
					has_prefix_addr, has_suffix_addr);
			if (d_name_ex_token == NULL)
				return (perror(ERROR_MALLOC), ft_lstclear(&for_check,
						free_expanding_token), FAILURE_BIN_R);
			ft_lstadd_back(replaced_d_names, d_name_ex_token);
		}
		entry = readdir(dir);
	}
	return (ft_lstclear(&for_check, free_expanding_token), SUCCESS_BIN_R);
}

t_binary_result	expand_wildcard_before_1st_separator(t_list *with_wildcd)
{
	DIR		*dir;
	t_list	*d_names_to_replace;

	if (with_wildcd == NULL)
		return (SUCCESS_BIN_R);
	d_names_to_replace = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (perror(ERROR_OPENDIR), FAILURE_BIN_R);
	if (retrieve_d_names_to_replace(dir, with_wildcd,
			&d_names_to_replace) == FAILURE_BIN_R)
		return (ft_lstclear(&d_names_to_replace, free_expanding_token),
			closedir(dir), FAILURE_BIN_R);
	closedir(dir);
	if (d_names_to_replace == NULL)
		return (SUCCESS_BIN_R);
	sort_ex_tokens_by_ascending(&d_names_to_replace);
	if (separate_quoted_ex_tokens(d_names_to_replace) == FAILURE_BIN_R)
		return (ft_lstclear(&d_names_to_replace, free_expanding_token),
			FAILURE_BIN_R);
	replace_wildcard_with_d_names(with_wildcd, d_names_to_replace);
	return (SUCCESS_BIN_R);
}

t_binary_result	expand_wildcard(t_list **ex_tokens)
{
	t_list			*current_token;
	t_binary_result	result;

	if (ex_tokens == NULL || *ex_tokens == NULL)
		return (SUCCESS_BIN_R);
	delete_prefix_separator(ex_tokens);
	current_token = *ex_tokens;
	while (current_token != NULL)
	{
		if (has_wildcard_before_1st_separator(current_token))
		{
			result = expand_wildcard_before_1st_separator(current_token);
			if (result == FAILURE_BIN_R)
				return (FAILURE_BIN_R);
		}
		to_next_separate_top(&current_token);
	}
	return (SUCCESS_BIN_R);
}
