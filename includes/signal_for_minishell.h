/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_for_minishell.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:31:29 by katakada          #+#    #+#             */
/*   Updated: 2025/06/02 19:30:29 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_FOR_MINISHELL_H
# define SIGNAL_FOR_MINISHELL_H

# include "minishell.h"

// signal__utils.c
int		nop_event_hook(void);

// signal.c
void	set_sig_handlers_in_dialog(void);
void	set_sig_handlers_in_exec_child(void);
void	set_sig_handlers_in_exec_parent(void);

#endif