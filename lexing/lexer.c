/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:47:32 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 20:53:07 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "t_minishell.h"

static int	lexicize_start_with_quote(char *input, t_list **token_list)
{
	char	quote;
	int		put_size;
	char	*ptr_input;

	quote = *input;
	ptr_input = input;
	put_size = lexicize_func_sign(ptr_input, token_list);
	if (put_size == FAILURE)
		return (FAILURE);
	ptr_input += put_size;
	if (*ptr_input == '\0')
		return (ptr_input - input);
	put_size = lexicize_text_in_quote(ptr_input, token_list, quote);
	if (put_size == FAILURE)
		return (FAILURE);
	ptr_input += put_size;
	if (*ptr_input == quote)
	{
		put_size = lexicize_func_sign(ptr_input, token_list);
		if (put_size == FAILURE)
			return (FAILURE);
		ptr_input += put_size;
	}
	return (ptr_input - input);
}

static int	lexicize_operator(char *input, t_list **token_list)
{
	return (lexicize_func_sign(input, token_list));
}

static int	lexicize_operand(char *input, t_list **token_list)
{
	int		lexicized_size;
	char	*ptr_input;

	ptr_input = input;
	while (*ptr_input && !is_operator(ptr_input))
	{
		if (is_quote(*ptr_input))
			lexicized_size = lexicize_start_with_quote(ptr_input, token_list);
		else
			lexicized_size = lexicize_text(ptr_input, token_list);
		if (lexicized_size == FAILURE)
			return (FAILURE);
		ptr_input += lexicized_size;
	}
	return (ptr_input - input);
}

// Noted: operand is the string sandwiched between operators
static int	lexicize_input(char *input, t_list **token_list)
{
	int	lexicized_size;

	if (is_operator(input))
		lexicized_size = lexicize_operator(input, token_list);
	else
		lexicized_size = lexicize_operand(input, token_list);
	return (lexicized_size);
}

int	lexer(char *input, t_list **token_list)
{
	int	lexicized_size;

	if (input == NULL)
		return (EXIT_S_FAILURE);
	while (*input)
	{
		if (is_ifs(*input))
			input++;
		else
		{
			lexicized_size = lexicize_input(input, token_list);
			if (lexicized_size == FAILURE)
				return (ft_lstclear(token_list, free_token), EXIT_S_FAILURE);
			input += lexicized_size;
		}
	}
	lexicized_size = append_terminator(token_list);
	if (lexicized_size == FAILURE)
		return (ft_lstclear(token_list, free_token), EXIT_S_FAILURE);
	return (EXIT_S_SUCCESS);
}
