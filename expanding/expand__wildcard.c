/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:07:15 by katakada          #+#    #+#             */
/*   Updated: 2025/05/25 23:38:12 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_print.h"

char	get_next_char(t_list **w_tokens, int *current_index)
{
	char	next_char;

	if (w_tokens == NULL || *w_tokens == NULL || current_index == NULL)
		return ('\0');
	if (get_ex_token(w_tokens)->type == ET_SEPARATOR)
		return ('\0');
	if (get_ex_token(w_tokens)->type == ET_WILDCARD)
	{
		while (*w_tokens != NULL && get_ex_token(w_tokens)->type == ET_WILDCARD)
			*w_tokens = (*w_tokens)->next;
		*current_index = 0;
		return ('*');
	}
	if (get_ex_token(w_tokens)->str[*current_index] == '\0')
	{
		*w_tokens = (*w_tokens)->next;
		*current_index = 0;
		return (get_next_char(w_tokens, current_index));
	}
	next_char = get_ex_token(w_tokens)->str[*current_index];
	(*current_index)++;
	return (next_char);
}

char	wrap_get_next_char(t_list *wildcard_in_tokens, t_bool is_first_call)
{
	static t_list	*current_token;
	static int		current_index;

	if (is_first_call)
	{
		if (wildcard_in_tokens == NULL)
			return ('\0');
		current_token = wildcard_in_tokens;
		current_index = 0;
	}
	return (get_next_char(&current_token, &current_index));
}

int	count_wildcard_in_tokens(t_list *wildcard_in_tokens)
{
	int	count;

	count = 0;
	if (wildcard_in_tokens == NULL)
		return (0);
	while (wildcard_in_tokens != NULL
		&& get_ex_token(&wildcard_in_tokens)->type != ET_SEPARATOR)
	{
		if (get_ex_token(&wildcard_in_tokens)->type == ET_WILDCARD)
			count++;
		wildcard_in_tokens = wildcard_in_tokens->next;
	}
	return (count);
}

int	get_last_ward_length(t_list *wildcard_in_tokens)
{
	int		last_ward_length;
	char	char_in_wildcard;

	if (wildcard_in_tokens == NULL)
		return (0);
	last_ward_length = 0;
	char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, TRUE);
	while (char_in_wildcard != '\0')
	{
		if (char_in_wildcard == '*')
		{
			last_ward_length = 0;
			char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
			if (char_in_wildcard == '\0')
				return (last_ward_length);
			while (char_in_wildcard != '\0' && char_in_wildcard != '*')
			{
				last_ward_length++;
				char_in_wildcard = wrap_get_next_char(wildcard_in_tokens,
						FALSE);
			}
		}
		else
		{
			last_ward_length++;
			char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
		}
	}
	return (last_ward_length);
}

t_bool	is_same_last_ward(char *d_name, t_list *wildcard_in_tokens)
{
	int		wildcard_count;
	int		last_ward_length;
	char	char_in_wildcard;
	int		i;

	wildcard_count = count_wildcard_in_tokens(wildcard_in_tokens);
	last_ward_length = get_last_ward_length(wildcard_in_tokens);
	if ((int)ft_strlen(d_name) < last_ward_length)
		return (FALSE);
	i = 0;
	char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, TRUE);
	while (char_in_wildcard != '\0' && i < wildcard_count)
	{
		if (char_in_wildcard == '*')
			i++;
		char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
	}
	i = ft_strlen(d_name) - last_ward_length;
	while (d_name[i] != '\0' && char_in_wildcard != '\0')
	{
		if (char_in_wildcard == '*')
			char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
		if (d_name[i] != char_in_wildcard)
			return (FALSE);
		i++;
		char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
	}
	if (char_in_wildcard == '\0')
		return (TRUE);
	return (FALSE);
}

t_bool	is_last_word(t_list *wildcard_in_tokens)
{
	char	char_in_wildcard;

	char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
	while (char_in_wildcard != '\0')
	{
		if (char_in_wildcard == '*')
			return (FALSE);
		char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
	}
	return (TRUE);
}

t_bool	can_expand_wildcard_to_name(char *d_name, t_list *wildcard_in_tokens)
{
	int		i;
	char	char_in_wildcard;

	if (wildcard_in_tokens == NULL || d_name == NULL)
		return (FALSE);
	i = 0;
	char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, TRUE);
	while (char_in_wildcard != '\0')
	{
		if (char_in_wildcard == '*')
		{
			char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
			if (char_in_wildcard == '\0')
				return (TRUE);
			while (d_name[i] != '\0' && d_name[i] != char_in_wildcard)
				i++;
		}
		if (d_name[i] == char_in_wildcard)
			i++;
		else
		{
			if (is_last_word(wildcard_in_tokens))
				break ;
			else
				return (FALSE);
		}
		char_in_wildcard = wrap_get_next_char(wildcard_in_tokens, FALSE);
	}
	return (is_same_last_ward(d_name, wildcard_in_tokens));
}

t_bool	has_2_prefix_in_ex_token(t_list *wildcard_in_tokens, char prefix_c1,
		char prefix_c2)
{
	if (wildcard_in_tokens == NULL)
		return (FALSE);
	while (wildcard_in_tokens != NULL
		&& get_ex_token(&wildcard_in_tokens)->type != ET_SEPARATOR
		&& get_ex_token(&wildcard_in_tokens)->str[0] == '\0')
		wildcard_in_tokens = wildcard_in_tokens->next;
	if (get_ex_token(&wildcard_in_tokens)->type == ET_DEATH_DOLLAR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_SEPARATOR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_WILDCARD
		|| get_ex_token(&wildcard_in_tokens)->str[0] != prefix_c1)
		return (FALSE);
	if (get_ex_token(&wildcard_in_tokens)->str[1] != '\0')
		return (get_ex_token(&wildcard_in_tokens)->str[1] == prefix_c1);
	wildcard_in_tokens = wildcard_in_tokens->next;
	while (wildcard_in_tokens != NULL
		&& get_ex_token(&wildcard_in_tokens)->type != ET_SEPARATOR
		&& get_ex_token(&wildcard_in_tokens)->str[0] == '\0')
		wildcard_in_tokens = wildcard_in_tokens->next;
	if (get_ex_token(&wildcard_in_tokens)->type == ET_DEATH_DOLLAR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_SEPARATOR
		|| get_ex_token(&wildcard_in_tokens)->type == ET_WILDCARD
		|| get_ex_token(&wildcard_in_tokens)->str[0] != prefix_c2)
		return (FALSE);
	return (TRUE);
}

t_bool	has_1_suffix_in_ex_token(t_list *wildcard_in_tokens, char suffix_c1)
{
	char				end_char;
	t_expanding_token	*ex_token;
	int					i;

	end_char = -1;
	if (wildcard_in_tokens == NULL)
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
	return (end_char == suffix_c1);
}

void	sort_ascending_list(t_list **wild_expanded_tokens)
{
	t_list				*current;
	t_list				*next;
	t_expanding_token	*current_token;
	t_expanding_token	*next_token;

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
				if (has_2_prefix_in_ex_token(wildcard_in_tokens, '.', '/'))
					wild_epanded_d_name = strjoin_free(ft_strdup("./"),
							wild_epanded_d_name);
				wild_epanded_d_name = strjoin_free(wild_epanded_d_name,
						ft_strdup(entry->d_name));
				if (has_1_suffix_in_ex_token(wildcard_in_tokens, '/'))
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
		entry = readdir(dir);
	}
	closedir(dir);
	if (wild_expanded_tokens == NULL)
		return (SUCCESS_BIN_R);
	sort_ascending_list(&wild_expanded_tokens);
	if (insert_separator_to_quoted_ex_tokens(wild_expanded_tokens) == FAILURE_BIN_R)
		return (free(wild_expanded_tokens), FAILURE_BIN_R);
	reconect_wild_expanded_list(wildcard_in_tokens, wild_expanded_tokens);
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
