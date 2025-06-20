/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:36:36 by katakada          #+#    #+#             */
/*   Updated: 2025/06/20 18:19:36 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signal_for_minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	handle_sigint_in_dialog(int signum)
{
	g_sig = signum;
	rl_replace_line("", 0);
	rl_done = TRUE;
}

void	set_sig_handlers_in_dialog(void)
{
	g_sig = 0;
	signal(SIGINT, handle_sigint_in_dialog);
	signal(SIGQUIT, SIG_IGN);
}

void	set_sig_handlers_in_exec_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_sig_handlers_in_exec_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
