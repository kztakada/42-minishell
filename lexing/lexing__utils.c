/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing__utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:32:36 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 15:08:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

int	is_quote(char c)
{
	if (lookup_dict(&c, QUOTE_DICT).in_d)
		return (TRUE);
	return (FALSE);
}

int	is_operator(char *str)
{
	if (lookup_dict(str, OPERATORS_DICT).in_d)
		return (TRUE);
	return (FALSE);
}

void	free_token(void *target)
{
	t_token	*token;

	token = (t_token *)target;
	if (token)
	{
		free(token->value);
		free(token);
	}
}
