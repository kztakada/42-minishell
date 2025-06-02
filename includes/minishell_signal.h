/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:34:47 by katakada          #+#    #+#             */
/*   Updated: 2025/06/01 20:42:04 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "minishell.h"

// signal.c
int		nop_event_hook(void);
int		heredoc_event_hook(void);
void	set_sig_handlers_in_dialog(void);

#endif