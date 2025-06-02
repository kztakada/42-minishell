/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal__utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:29:12 by katakada          #+#    #+#             */
/*   Updated: 2025/06/02 19:29:48 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_for_minishell.h"

// event_hook
// rl_event_hook func:
// 0: continue reading input
// non zero: stop reading input
int	nop_event_hook(void)
{
	return (0);
}

// int	heredoc_event_hook(void)
// {
// 	if (g_sig == SIGINT)
// 	{
// 		// rl_done = TRUE;
// 	}
// 	return (0); // continue reading input
// }
