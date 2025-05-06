/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar__prefix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:28:18 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 00:34:16 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
#define NG_USE_FIRST " && || |"

static t_bool	can_use_as_first_token(t_token *test_token)
{
	if (is_in(NG_USE_FIRST, test_token))
		return (FALSE);
	return (TRUE);
}

int	grammar_prefix(t_token *test_token, int subshell_depth)
{
	if (test_token->id != 0)
		return (OK);
	if (test_token == NULL)
		return (FALSE);
	if (can_use_as_first_token(test_token) == FALSE)
		return (NG);
	if (subshell_depth == 0 && test_token->type == OP_CLOSE)
		return (NG);
	return (OK);
}
