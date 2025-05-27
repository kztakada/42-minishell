/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander__utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:43:16 by katakada          #+#    #+#             */
/*   Updated: 2025/05/27 01:04:51 by katakada         ###   ########.fr       */
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

t_expanding_token	*get_ex_token(t_list **expanding_tokens)
{
	t_expanding_token	*expanding_token;

	if (*expanding_tokens == NULL)
		return (NULL);
	expanding_token = (t_expanding_token *)(*expanding_tokens)->content;
	return (expanding_token);
}

void	sort_ex_list_by_ascending(t_list **expanded_tokens)
{
	t_list				*current;
	t_list				*next;
	t_expanding_token	*current_token;
	t_expanding_token	*next_token;

	if (expanded_tokens == NULL || *expanded_tokens == NULL)
		return ;
	current = *expanded_tokens;
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
