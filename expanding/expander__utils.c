/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander__utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:43:16 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 04:09:20 by katakada         ###   ########.fr       */
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
