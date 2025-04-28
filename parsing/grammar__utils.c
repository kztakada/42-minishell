/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:05:51 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 15:22:14 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

void	forward_token_list(t_list **current_token_list)
{
	*current_token_list = (*current_token_list)->next;
}

t_token	*get_token(t_list *current_token)
{
	t_token	*token;

	token = (t_token *)current_token->content;
	return (token);
}

t_bool	is_in(t_token *testing_token, char *dict)
{
	return (lookup_dict(testing_token->value, dict).in_d);
}

// grammar number finder
int	gf(t_token *testing_token, char *dict)
{
	return (lookup_dict(testing_token->value, dict).d_index);
}
