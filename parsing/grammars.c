/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:02:45 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 22:41:29 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_bool	can_use_as_first_token(t_token *token)
{
	if (token == NULL)
		return (FALSE);
	if (lookup_dict(token->value, NO_USE_FIRST).in_d)
		return (FALSE);
	return (TRUE);
}
