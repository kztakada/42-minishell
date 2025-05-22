/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:11:14 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 23:12:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

t_bool	is_ambiguous_redirection(t_list *expanding_tokens)
{
	int	arg_count;

	arg_count = get_arg_size(expanding_tokens);
	if (arg_count == 0)
		return (TRUE);
	if (arg_count == 1)
		return (FALSE);
	else
		return (TRUE);
}

void	put_ambiguous_redirection_err(t_list *file_name_words)
{
	t_list			*current_word;
	t_parsed_word	*parsed_word;

	if (file_name_words == NULL)
		return ;
	current_word = file_name_words;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	while (current_word != NULL)
	{
		parsed_word = (t_parsed_word *)current_word->content;
		if (parsed_word->type == W_SINGLE_QUOTED)
			ft_putstr_fd("'", STDERR_FILENO);
		else if (parsed_word->type == W_DOUBLE_QUOTED)
			ft_putstr_fd("\"", STDERR_FILENO);
		ft_putstr_fd(parsed_word->str, STDERR_FILENO);
		if (parsed_word->type == W_SINGLE_QUOTED)
			ft_putstr_fd("'", STDERR_FILENO);
		else if (parsed_word->type == W_DOUBLE_QUOTED)
			ft_putstr_fd("\"", STDERR_FILENO);
		current_word = current_word->next;
	}
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
}
