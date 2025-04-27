/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_following_subshell.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 21:45:54 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 00:26:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	check_following_sub_open(t_list **follower_list, int *subshell_count)
{
	(void)follower_list;
	(*subshell_count)++;
	return (OK);
}

int	check_following_sub_close(t_list **follower_list, int *subshell_count)
{
	if (*subshell_count == 0)
		return (NG);
	if (is_in(get_token(*follower_list), SUBSHELL_OP))
		return (NG);
	(*subshell_count)--;
	(void)follower_list;
	return (OK);
}

// terminator
int	check_following_terminator(t_list **follower_list, int *subshell_count)
{
	(void)follower_list;
	if (*subshell_count > 0)
		return (NG);
	return (OK);
}
