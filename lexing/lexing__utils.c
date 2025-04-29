/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing__utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:32:36 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 19:19:15 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	is_ifs(char c)
{
	if (lookup_dict(&c, IFS_DICT).in_d)
		return (TRUE);
	return (FALSE);
}

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
