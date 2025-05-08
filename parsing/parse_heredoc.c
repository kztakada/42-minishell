/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 04:35:05 by katakada          #+#    #+#             */
/*   Updated: 2025/05/07 22:24:01 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_exit_status	parse_heredoc(t_list *input_tokens, t_list *next_tokens,
		t_abs_node **abs_tree, t_parse_log *perse_log)
{
	t_list	*heredoc;

	(void)next_tokens;
	(void)abs_tree;
	heredoc = ft_lstnew(get_token(input_tokens));
	if (heredoc == NULL)
		return (EXIT_FAILURE);
	ft_lstadd_back(&(perse_log->heredoc_list), heredoc);
	return (EXIT_S_SUCCESS);
}

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
