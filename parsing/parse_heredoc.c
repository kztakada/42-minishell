/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 04:35:05 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 21:47:54 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

void	call_heredoc(t_parse_log *parse_log)
{
	t_list	*current;

	current = parse_log->heredoc_list;
	while (current)
	{
		ft_putstr_fd("heredoc exec\n", STDOUT_FILENO);
		current = current->next;
	}
	ft_lstclear(&(parse_log->heredoc_list), no_del);
}
