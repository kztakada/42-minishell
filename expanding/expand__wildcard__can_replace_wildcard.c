/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__wildcard__can_replace_wildcard.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:13:38 by katakada          #+#    #+#             */
/*   Updated: 2025/05/27 20:15:36 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_bool	is_hidden_file(t_list *for_wildcd_check)
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

static t_bool	is_ends_in_wildcard(t_list *for_wildcd_check)
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

static t_bool	wd_check_by_list_count(char *d_name, t_list *for_wildcd_check,
		int list_size)
{
	int	i;

	i = 0;
	while (for_wildcd_check != NULL && list_size > 0)
	{
		if (get_ex_token(&for_wildcd_check)->type == ET_WILDCARD)
		{
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

static t_bool	wd_check_by_ends_in_str(char *d_name, t_list *for_wildcd_check,
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

t_bool	can_replace_wildcard(char *d_name, t_list *for_wildcd_check)
{
	if (for_wildcd_check == NULL || d_name == NULL)
		return (FALSE);
	ft_lstsize(for_wildcd_check);
	if (!is_hidden_file(for_wildcd_check) && d_name[0] == '.')
		return (FALSE);
	if (is_hidden_file(for_wildcd_check) && d_name[0] != '.')
		return (FALSE);
	if (is_ends_in_wildcard(for_wildcd_check))
		return (wd_check_by_list_count(d_name, for_wildcd_check,
				ft_lstsize(for_wildcd_check)));
	else
		return (wd_check_by_ends_in_str(d_name, for_wildcd_check,
				ft_lstsize(for_wildcd_check)));
}
