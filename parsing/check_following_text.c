/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following_text.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:51:44 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 00:25:15 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	check_following_quote_single(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}

int	check_following_quote_double(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}

int	check_following_operand_text(t_token *testing_token, t_list **follower_list)
{
	(void)testing_token;
	(void)follower_list;
	return (OK);
}
