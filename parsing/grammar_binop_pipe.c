/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_binop_pipe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:01:41 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 15:01:42 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

// binary operators
int	grammar_binop_and(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}

int	grammar_binop_or(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}

// pipe
int	grammar_pipe(t_list **follower_list)
{
	(void)follower_list;
	return (OK);
}
