/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_subshell__util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:06:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/04 21:00:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static int	get_second_word_index(char *str)
{
	int	second_word_index;
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_ifs(str[i]))
			break ;
		i++;
	}
	second_word_index = i + 1;
	if (str[second_word_index] == '\0')
		return (-1);
	return (second_word_index);
}

int	grammar_sub_close_to_redirect(t_list **next_tokens)
{
	t_token	*next_to_redirect_token;
	int		second_word_index;
	char	*for_free;

	next_to_redirect_token = get_token((*next_tokens)->next);
	if (next_to_redirect_token->type != OPERAND_TEXT)
		return (OK);
	second_word_index = get_second_word_index(next_to_redirect_token->value);
	if (second_word_index == -1)
		return (OK);
	for_free = next_to_redirect_token->value;
	next_to_redirect_token->value = ft_substr(next_to_redirect_token->value,
			second_word_index, ft_strlen(next_to_redirect_token->value)
			- second_word_index + 1);
	if (next_to_redirect_token->value == NULL)
		return (perror(ERROR_MALLOC), NG);
	free(for_free);
	*next_tokens = (*next_tokens)->next;
	return (NG);
}
