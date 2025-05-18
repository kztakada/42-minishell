/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander__utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:43:16 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 20:53:53 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

void	free_expanding_token(void *content)
{
	t_expanding_token	*expanding_token;

	expanding_token = (t_expanding_token *)content;
	if (expanding_token->str != NULL)
		free(expanding_token->str);
	free(expanding_token);
}

// 未実装
char	**expanding_tokens_to_str_list(t_list *expanding_tokens)
{
	t_list				*current;
	t_expanding_token	*expanding_token;
	char				**str_list;
	char				*str;
	int					i;
	int					count;

	i = 0;
	count = 0;
	current = expanding_tokens;
	while (current != NULL)
	{
		expanding_token = (t_expanding_token *)current->content;
		if (expanding_token->type == ET_EXPANDED_STR)
			count++;
		current = current->next;
	}
	str_list = (char **)malloc(sizeof(char *) * (count + 1));
	if (str_list == NULL)
		return (NULL);
	current = expanding_tokens;
	while (current != NULL)
	{
		expanding_token = (t_expanding_token *)current->content;
		if (expanding_token->type == ET_EXPANDED_STR)
		{
			str = ft_strdup(expanding_token->str);
			if (str == NULL)
				return (NULL);
			str_list[i] = str;
			str_list[i + 1] = NULL;
			i++;
		}
		current = current->next;
	}
	return (str_list);
}
