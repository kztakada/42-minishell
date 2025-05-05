/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:05:51 by katakada          #+#    #+#             */
/*   Updated: 2025/05/05 18:20:34 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_list	**forward_token_list(t_list **current_token_list)
{
	*current_token_list = (*current_token_list)->next;
	return (current_token_list);
}

t_token	*get_token(t_list *current_token)
{
	t_token	*token;

	token = (t_token *)current_token->content;
	return (token);
}

t_bool	is_in(char *dict, t_token *test_token)
{
	return (lookup_dict(test_token->value, dict).in_d);
}

t_bool	is_operand_text(t_token *test_token)
{
	if (test_token->type == OPERAND_TEXT)
		return (TRUE);
	return (FALSE);
}

// grammar(index number) finder
int	gf(t_token *testing_token, char *dict)
{
	return (lookup_dict(testing_token->value, dict).d_index);
}
