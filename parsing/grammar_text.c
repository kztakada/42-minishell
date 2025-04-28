/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:44 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 15:04:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	grammar_quote_single(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}

int	grammar_quote_double(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}

int	grammar_operand_text(t_token *testing_token, t_list **follower_list)
{
	(void)testing_token;
	(void)follower_list;
	return (OK);
}
