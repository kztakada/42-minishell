/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_abs_node__expanding_tokens_to_arg_li        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 04:08:51 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 18:36:48 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#define NULL_COUNT 1

int	get_arg_size(t_list *expanding_tokens)
{
	t_list	*current_token;
	int		arg_count;

	arg_count = 0;
	if (expanding_tokens == NULL)
		return (arg_count);
	if (get_ex_token(&expanding_tokens)->type != ET_SEPARATOR)
		arg_count++;
	current_token = expanding_tokens;
	while (current_token != NULL)
	{
		to_next_separate_top(&current_token);
		if (current_token == NULL)
			break ;
		if (get_ex_token(&current_token)->type != ET_SEPARATOR)
			arg_count++;
	}
	return (arg_count);
}

static char	*append_expanding_token_to_str(char *origin_str,
		t_list *expanding_tokens)
{
	if (expanding_tokens == NULL)
		return (NULL);
	if (get_ex_token(&expanding_tokens)->type == ET_WILDCARD)
		return (ft_strjoin(origin_str, "*"));
	else if (get_ex_token(&expanding_tokens)->type == ET_DEATH_DOLLAR)
		return (ft_strjoin(origin_str, "$"));
	else
	{
		if (get_ex_token(&expanding_tokens)->str == NULL)
			return (ft_strjoin(origin_str, ""));
		else
			return (ft_strjoin(origin_str,
					get_ex_token(&expanding_tokens)->str));
	}
}

static char	*expanding_tokens_to_str(t_list *expanding_tokens)
{
	char	*str;
	char	*tmp;

	str = ft_strdup("");
	if (str == NULL)
		return (perror(ERROR_MALLOC), NULL);
	while (expanding_tokens != NULL
		&& get_ex_token(&expanding_tokens)->type != ET_SEPARATOR)
	{
		tmp = str;
		str = append_expanding_token_to_str(str, expanding_tokens);
		if (str == NULL)
			return (free(tmp), perror(ERROR_MALLOC), NULL);
		free(tmp);
		expanding_tokens = expanding_tokens->next;
	}
	return (str);
}

char	**expanding_tokens_to_arg_list(t_list *expanding_tokens)
{
	t_list	*current_token;
	char	**arg_list;
	int		arg_count;
	int		i;

	arg_count = get_arg_size(expanding_tokens);
	current_token = expanding_tokens;
	arg_list = (char **)malloc(sizeof(char *) * (arg_count + NULL_COUNT));
	if (arg_list == NULL)
		return (perror(ERROR_MALLOC), NULL);
	i = 0;
	while (i < arg_count + NULL_COUNT)
		arg_list[i++] = NULL;
	current_token = expanding_tokens;
	i = 0;
	while (current_token != NULL)
	{
		arg_list[i] = expanding_tokens_to_str(current_token);
		if (arg_list[i] == NULL)
			return (free_str_list_by_size(arg_list, arg_count + NULL_COUNT),
				NULL);
		to_next_separate_top(&current_token);
		i++;
	}
	return (arg_list);
}
