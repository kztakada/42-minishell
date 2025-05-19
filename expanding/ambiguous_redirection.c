/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:11:14 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 03:20:36 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

// 未実装
// t_bool	is_ambiguous_redirection(t_list *expanding_tokens)
// {
// 	t_list	*current;

// 	current = expanding_tokens;
// 	while (current != NULL)
// 	{
// 		if (((t_expanding_token *)current->content)->type == ET_WILDCARD)
// 			return (TRUE);
// 		current = current->next;
// 	}
// 	return (FALSE);
// }

// 未実装
// void	put_ambiguous_redirection_err(t_list *file_name_words)
// {
// 	t_parsed_word	*parsed_word;

// 	parsed_word = (t_parsed_word *)file_name_words->content;
// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
// 	ft_putstr_fd(parsed_word->str, STDERR_FILENO);
// 	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
// }
