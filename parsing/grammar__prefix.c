/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:28:18 by katakada          #+#    #+#             */
/*   Updated: 2025/04/30 01:00:38 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_bool	can_use_as_first_token(t_token *test_token)
{
	if (is_in(NG_USE_FIRST, test_token))
		return (FALSE);
	return (TRUE);
}

int	grammar_prefix(t_token *test_token)
{
	if (test_token->id != 0)
		return (OK);
	if (test_token == NULL)
		return (FALSE);
	if (can_use_as_first_token(test_token) == FALSE)
		return (NG);
	return (OK);
}
