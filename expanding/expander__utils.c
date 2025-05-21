/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander__utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:43:16 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 03:26:36 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

#define NULL_COUNT 1

void	free_expanding_token(void *content)
{
	t_expanding_token	*expanding_token;

	expanding_token = (t_expanding_token *)content;
	if (expanding_token->str != NULL)
		free(expanding_token->str);
	free(expanding_token);
}

t_expanding_token	*get_ex_token(t_list **expanding_tokens)
{
	t_expanding_token	*expanding_token;

	if (*expanding_tokens == NULL)
		return (NULL);
	expanding_token = (t_expanding_token *)(*expanding_tokens)->content;
	return (expanding_token);
}

void	free_str_list_by_size(char **str_list, int str_list_size)
{
	int	i;

	if (str_list == NULL)
		return ;
	i = 0;
	while (i < str_list_size)
	{
		if (str_list[i] != NULL)
			free(str_list[i]);
		i++;
	}
	free(str_list);
}

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

char	*expanding_tokens_to_str(t_list *expanding_tokens)
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
		if (get_ex_token(&expanding_tokens)->type == ET_WILDCARD)
			str = ft_strjoin(str, "*");
		else if (get_ex_token(&expanding_tokens)->type == ET_DEATH_DOLLAR)
			str = ft_strjoin(str, "$");
		else
		{
			if (get_ex_token(&expanding_tokens)->str == NULL)
				str = ft_strjoin(str, "");
			else
				str = ft_strjoin(str, get_ex_token(&expanding_tokens)->str);
		}
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
