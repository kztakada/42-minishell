/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:28:18 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 15:28:19 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_bool	can_use_as_first_token(t_token *token)
{
	if (token == NULL)
		return (FALSE);
	if (lookup_dict(token->value, NO_USE_FIRST).in_d)
		return (FALSE);
	return (TRUE);
}

int	grammar_prefix(t_token *testing_token)
{
	if (can_use_as_first_token(testing_token) == FALSE)
		return (NG);
	return (OK);
}
