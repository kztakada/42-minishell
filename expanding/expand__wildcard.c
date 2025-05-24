/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:15 by katakada          #+#    #+#             */
/*   Updated: 2025/05/25 03:47:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_print.h"

t_bool	can_expand_wildcard_to_name(char *d_name, t_list *wildcard_in_tokens)
{
	(void)d_name;
	(void)wildcard_in_tokens;
	return (true);
}

t_bool	has_2_prefix_in_ex_token(t_list *wildcard_in_tokens, char *prefix)
{
	if (wildcard_in_tokens == NULL || prefix == NULL)
		return (FALSE);
	while (wildcard_in_tokens != NULL
		&& get_ex_token(&wildcard_in_tokens)->type != ET_SEPARATOR
		&& get_ex_token(&wildcard_in_tokens)->str[0] == '\0')
		wildcard_in_tokens = wildcard_in_tokens->next;
	if (get_ex_token(&wildcard_in_tokens)->type == ET_DEATH_DOLLAR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_SEPARATOR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_WILDCARD
		|| get_ex_token(&wildcard_in_tokens)->str[0] != prefix[0])
		return (FALSE);
	if (get_ex_token(&wildcard_in_tokens)->str[1] != '\0')
		return (get_ex_token(&wildcard_in_tokens)->str[1] == prefix[1]);
	wildcard_in_tokens = wildcard_in_tokens->next;
	while (wildcard_in_tokens != NULL
		&& get_ex_token(&wildcard_in_tokens)->type != ET_SEPARATOR
		&& get_ex_token(&wildcard_in_tokens)->str[0] == '\0')
		wildcard_in_tokens = wildcard_in_tokens->next;
	if (get_ex_token(&wildcard_in_tokens)->type == ET_DEATH_DOLLAR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_SEPARATOR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_WILDCARD
		|| get_ex_token(&wildcard_in_tokens)->str[0] != prefix[1])
		return (FALSE);
	return (TRUE);
}

t_bool	has_1_suffix_in_ex_token(t_list *wildcard_in_tokens, char *prefix)
{
	char				end_char;
	t_expanding_token	*ex_token;
	int					i;

	end_char = -1;
	if (wildcard_in_tokens == NULL || prefix == NULL)
		return (FALSE);
	while (wildcard_in_tokens != NULL
		&& get_ex_token(&wildcard_in_tokens)->type != ET_SEPARATOR)
	{
		ex_token = (t_expanding_token *)wildcard_in_tokens->content;
		i = 0;
		if (ex_token->type != ET_SEPARATOR)
		{
			while (ex_token->str[i] != '\0')
			{
				end_char = ex_token->str[i];
				i++;
			}
		}
		wildcard_in_tokens = wildcard_in_tokens->next;
	}
	if (end_char == -1)
		return (FALSE);
	return (end_char == prefix[0]);
}

void	ft_swap(void **a, void **b)
{
	void	*temp;

	if (a == NULL || b == NULL || *a == NULL || *b == NULL)
		return ;
	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_ascending_list(t_list **wild_expanded_tokens)
{
	t_list				*current;
	t_list				*next;
	t_expanding_token	*current_token;
	t_expanding_token	*next_token;

	// 未検証
	if (wild_expanded_tokens == NULL || *wild_expanded_tokens == NULL)
		return ;
	current = *wild_expanded_tokens;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			current_token = (t_expanding_token *)current->content;
			next_token = (t_expanding_token *)next->content;
			if (ft_strcmp(current_token->str, next_token->str) > 0)
			{
				ft_swap(&current->content, &next->content);
			}
			next = next->next;
		}
		current = current->next;
	}
}

t_binary_result	expand_wildcard_before_1st_separator(t_list *wildcard_in_tokens)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*under_expanding;
	t_list			*wild_expanded_tokens;
	char			*wild_epanded_d_name;

	if (wildcard_in_tokens == NULL)
		return (SUCCESS_BIN_R);
	wild_expanded_tokens = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (perror("opendir"), FAILURE_BIN_R);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (ft_strcmp(entry->d_name, ".") != 0 && ft_strcmp(entry->d_name,
				"..") != 0 && entry->d_name[0] != '.')
		{
			if (can_expand_wildcard_to_name(entry->d_name, wildcard_in_tokens))
			{
				wild_epanded_d_name = ft_strdup("");
				if (has_2_prefix_in_ex_token(wildcard_in_tokens, "./"))
					wild_epanded_d_name = strjoin_free(ft_strdup("./"),
							wild_epanded_d_name);
				wild_epanded_d_name = strjoin_free(wild_epanded_d_name,
						ft_strdup(entry->d_name));
				if (has_1_suffix_in_ex_token(wildcard_in_tokens, "/"))
					wild_epanded_d_name = strjoin_free(wild_epanded_d_name,
							ft_strdup("/"));
				under_expanding = expand_single_quoted_word(wild_epanded_d_name);
				if (under_expanding == NULL)
					return (free(wild_expanded_tokens),
						free(wild_epanded_d_name), closedir(dir),
						FAILURE_BIN_R);
				ft_lstadd_back(&wild_expanded_tokens, under_expanding);
			}
		}
		// printf("Found file: %s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	if (wild_expanded_tokens == NULL)
		return (SUCCESS_BIN_R);
	sort_ascending_list(&wild_expanded_tokens);
	if (insert_separator_to_quoted_ex_tokens(wild_expanded_tokens) == FAILURE_BIN_R)
		return (free(wild_expanded_tokens), FAILURE_BIN_R);
	// print_expanding_token_list(wild_expanded_tokens); // テスト用
	reconect_wild_expanded_list(wildcard_in_tokens, wild_expanded_tokens);
	// printf("reconect_wild_expanded_list\n");
	// print_expanding_token_list(wildcard_in_tokens); // テスト用
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
