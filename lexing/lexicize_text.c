/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicize_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:11:52 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:33:49 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

static int	get_text_len(char *input)
{
	int	operand_len;

	operand_len = 0;
	while (input[operand_len] && !is_operator(input + operand_len)
		&& !is_quote(input[operand_len]))
	{
		operand_len++;
	}
	return (operand_len);
}

static int	get_quoted_text_len(char *input, char quote)
{
	int	quoted_text_len;

	quoted_text_len = 0;
	while (input[quoted_text_len] && input[quoted_text_len] != quote)
	{
		quoted_text_len++;
	}
	return (quoted_text_len);
}

static t_token	*get_text_token(char *input, int text_len)
{
	t_token	*allocated_token;

	if (!input || !*input)
		return (NULL);
	allocated_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (allocated_token == NULL)
		return (perror(ERROR_MALLOC), NULL);
	allocated_token->type = OPERAND_TEXT;
	allocated_token->value = ft_substr(input, 0, text_len);
	if (allocated_token->value == NULL)
	{
		free(allocated_token);
		return (perror(ERROR_MALLOC), NULL);
	}
	return (allocated_token);
}

int	lexicize_text(char *input, t_list **token_list)
{
	t_token	*token;
	int		text_len;
	int		lexicized_size;

	if (!input || !*input)
		return (FAILURE);
	text_len = get_text_len(input);
	token = get_text_token(input, text_len);
	if (!token)
		return (FAILURE);
	lexicized_size = add_token_to_list(token, token_list);
	if (lexicized_size == FAILURE)
	{
		free_token(token);
		return (FAILURE);
	}
	return (lexicized_size);
}

int	lexicize_text_in_quote(char *input, t_list **token_list, char quote)
{
	t_token	*token;
	int		text_len;
	int		lexicized_size;

	if (!input || !*input)
		return (FAILURE);
	text_len = get_quoted_text_len(input, quote);
	token = get_text_token(input, text_len);
	if (!token)
		return (FAILURE);
	lexicized_size = add_token_to_list(token, token_list);
	return (lexicized_size);
}
