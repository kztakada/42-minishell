/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:36:36 by katakada          #+#    #+#             */
/*   Updated: 2025/06/01 20:41:51 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_signal.h"

volatile sig_atomic_t	g_sig = 0;

// event_hook ************************************************
// rl_event_hook func:
// 0: continue reading input
// non zero: stop reading input
int	nop_event_hook(void)
{
	return (0);
}

int	heredoc_event_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_done = TRUE;
	}
	return (0); // continue reading input
}

// ************************************************************

static void	handle_sigint_in_dialog(int signum)
{
	g_sig = signum;
	rl_replace_line("", 0);
	rl_done = 1;
}

void	set_sig_handlers_in_dialog(void)
{
	signal(SIGINT, handle_sigint_in_dialog);
	signal(SIGQUIT, SIG_IGN);
}
