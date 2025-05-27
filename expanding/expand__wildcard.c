/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:15 by katakada          #+#    #+#             */
/*   Updated: 2025/05/27 19:56:31 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_print.h"
#define ENDS_IN_WILDCARD -1

t_bool	is_hidden_file(t_list *for_wildcd_check)
{
	if (for_wildcd_check == NULL)
		return (FALSE);
	if (get_ex_token(&for_wildcd_check)->type == ET_WILDCARD)
		return (FALSE);
	if (get_ex_token(&for_wildcd_check)->type == ET_QUOTED_STR
		&& get_ex_token(&for_wildcd_check)->str[0] == '.')
		return (TRUE);
	if (get_ex_token(&for_wildcd_check)->type == ET_UNQUOTED_STR
		&& get_ex_token(&for_wildcd_check)->str[0] == '.')
		return (TRUE);
	return (FALSE);
}

// 頭から文字列をstrncmpでチェックして、該当すれば、その文字列の長さ分、iを次に送る
// 該当しなければその時点でFALSE
// ＊の場合は、その次の文字列と合致するまで、判定を送る（＊の次の文字列が無かったらTRUE）
// ＊の判定送り中に、最後まで行きついたら、FALSE
t_bool	wd_check_by_list_count(char *d_name, t_list *for_wildcd_check,
		int list_size)
{
	int	i;

	i = 0;
	// print_expanding_token_list(for_wildcd_check);
	// printf("d_name: %s\n", d_name);
	// printf("list_size: %d\n", list_size);
	while (for_wildcd_check != NULL && list_size > 0)
	{
		// printf("ping\n");
		if (get_ex_token(&for_wildcd_check)->type == ET_WILDCARD)
		{
			// printf("pong\n");
			forward_token_list(&for_wildcd_check);
			if (for_wildcd_check == NULL)
				return (TRUE);
			while (d_name[i] != '\0' && ft_strncmp(d_name + i,
					get_ex_token(&for_wildcd_check)->str,
					ft_strlen(get_ex_token(&for_wildcd_check)->str)) != 0)
				i++;
		}
		if (ft_strncmp(d_name + i, get_ex_token(&for_wildcd_check)->str,
				ft_strlen(get_ex_token(&for_wildcd_check)->str)) != 0)
			return (FALSE);
		i += ft_strlen(get_ex_token(&for_wildcd_check)->str);
		for_wildcd_check = for_wildcd_check->next;
		list_size--;
	}
	return (TRUE);
}

t_bool	wd_check_by_ends_in_str(char *d_name, t_list *for_wildcd_check,
		int list_size)
{
	if (wd_check_by_list_count(d_name, for_wildcd_check, list_size
			- 1) == FALSE)
		return (FALSE);
	for_wildcd_check = ft_lstlast(for_wildcd_check);
	if (ft_strcmp(d_name + ft_strlen(d_name)
			- ft_strlen(get_ex_token(&for_wildcd_check)->str),
			get_ex_token(&for_wildcd_check)->str) != 0)
		return (FALSE);
	return (TRUE);
}

t_bool	is_ends_in_wildcard(t_list *for_wildcd_check)
{
	t_bool	result;

	if (for_wildcd_check == NULL)
		return (FALSE);
	while (for_wildcd_check != NULL)
	{
		if (get_ex_token(&for_wildcd_check)->type == ET_WILDCARD)
			result = TRUE;
		else
			result = FALSE;
		for_wildcd_check = for_wildcd_check->next;
	}
	return (result);
}

t_bool	can_replace_wildcard(char *d_name, t_list *for_wildcd_check)
{
	if (for_wildcd_check == NULL || d_name == NULL)
		return (FALSE);
	ft_lstsize(for_wildcd_check);
	// 判定ブロック
	// 頭文字が.で始まっていなかったら、.始まりを除外する
	// printf("for_wildcd_check: %s\n", get_ex_token(&for_wildcd_check)->str);
	// printf("is_hidden_file: %d\n", is_hidden_file(for_wildcd_check));
	if (!is_hidden_file(for_wildcd_check) && d_name[0] == '.')
		return (FALSE);
	if (is_hidden_file(for_wildcd_check) && d_name[0] != '.')
		return (FALSE);
	// 最後が＊ではなかったら、最後の文字列はケツ合わせで確認する
	if (is_ends_in_wildcard(for_wildcd_check))
		return (wd_check_by_list_count(d_name, for_wildcd_check,
				ft_lstsize(for_wildcd_check)));
	else
		return (wd_check_by_ends_in_str(d_name, for_wildcd_check,
				ft_lstsize(for_wildcd_check)));
}

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
	d_name_ex_token = expand_single_quoted_word(d_name_copy);
	if (d_name_ex_token == NULL)
		return (free(d_name_copy), NULL);
	return (d_name_ex_token);
}

t_binary_result	delete_prefix_adrr(t_list **for_check, t_bool *has_prefix_addr)
{
	t_list	*tmp_list;
	char	*tmp_str;

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

void	delete_last_list(t_list *for_check)
{
	t_list	*last;
	t_list	*prev;

	if (for_check == NULL)
		return ;
	last = ft_lstlast(for_check);
	if (last == NULL)
		return ;
	prev = for_check;
	while (prev->next != last)
		prev = prev->next;
	ft_lstdelone(last, free_expanding_token);
	prev->next = NULL;
}

t_binary_result	delete_suffix_adrr(t_list *for_check, t_bool *has_suffix_addr)
{
	t_list	*origin;

	origin = for_check;
	if (for_check == NULL)
		return (SUCCESS_BIN_R);
	for_check = ft_lstlast(for_check);
	if ((get_ex_token(&for_check)->type != ET_UNQUOTED_STR
			&& get_ex_token(&for_check)->type != ET_QUOTED_STR))
		return (SUCCESS_BIN_R);
	if (ft_strcmp(get_ex_token(&for_check)->str, "/") == 0)
	{
		delete_last_list(origin);
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

	// 前工�����������������ブロ���ク
	// ����ずは���ex_tokenのリストを、文字の塊と＊だけのリストに�����
	// その時に、
	// ./で始まっていたら、頭の２文字を除外する
	// /で終わっていたら、最���を�����外する
	// ＊が続いたら、１つだけにする
	// 最後���空���字で終わる場合はリストは作らない
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

t_binary_result	retrieve_d_names_to_replace(DIR *dir, t_list *with_wildcd,
		t_list **replaced_d_names)
{
	struct dirent	*entry;
	t_list			*d_name_ex_token;
	t_list			*for_check;
	t_bool			has_prefix_addr;
	t_bool			has_suffix_addr;

	has_prefix_addr = FALSE;
	has_suffix_addr = FALSE;
	for_check = extract_tokens_for_wildcard_check(with_wildcd, &has_prefix_addr,
			&has_suffix_addr);
	if (for_check == NULL)
		return (perror(ERROR_MALLOC), FAILURE_BIN_R);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (can_replace_wildcard(entry->d_name, for_check))
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
		return (perror("opendir"), FAILURE_BIN_R);
	if (retrieve_d_names_to_replace(dir, with_wildcd,
			&d_names_to_replace) == FAILURE_BIN_R)
		return (ft_lstclear(&d_names_to_replace, free_expanding_token),
			closedir(dir), FAILURE_BIN_R);
	closedir(dir);
	if (d_names_to_replace == NULL)
		return (SUCCESS_BIN_R);
	sort_ex_list_by_ascending(&d_names_to_replace);
	if (insert_separator_to_quoted_ex_tokens(d_names_to_replace) == FAILURE_BIN_R)
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
