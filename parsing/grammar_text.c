/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:44 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 18:05:36 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	grammar_quote_single(t_list **next_tokens)
{
	(void)next_tokens;
	return (OK);
}

int	grammar_quote_double(t_list **next_tokens)
{
	(void)next_tokens;
	return (OK);
}

int	grammar_operand_text(t_token *testing_token, t_list **next_tokens)
{
	(void)testing_token;
	(void)next_tokens;
	return (OK);
}
