/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:04:44 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:27:17 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

#define NG_NEXT_TO_O_TEXT " ("

// " << >> && || | < > ( ) ' \" \n"

static t_bool	could_remove_1st_arg(t_token *token)
{
	char	*arg_str;
	int		i;

	arg_str = token->value;
	i = 0;
	if (is_ifs(arg_str[i]))
	{
		i++;
		while (is_ifs(arg_str[i]))
			i++;
	}
	else
	{
		while (!is_ifs(arg_str[i]))
			i++;
		while (is_ifs(arg_str[i]))
			i++;
	}
	if (arg_str[i] == '\0')
		return (FALSE);
	token->value = ft_substr(arg_str, i, ft_strlen(arg_str) - i + 1);
	if (token->value == NULL)
		return (perror(ERROR_MALLOC), FALSE);
	free(arg_str);
	return (TRUE);
}

static int	check_strict_2nd_arg(t_list **next_tokens, t_bool *strict_mode)
{
	*strict_mode = FALSE;
	if (could_remove_1st_arg(get_token(*next_tokens)) == TRUE)
		return (NG_G);
	forward_token_list(next_tokens);
	if (is_in(QUOTE_DICT, get_token(*next_tokens)))
		return (NG_G);
	else
		return (OK_G);
}

int	grammar_operand_text(t_token *testing_token, t_list **next_tokens,
		int subshell_depth, t_bool *strict_mode)
{
	(void)testing_token;
	if (*strict_mode == TRUE)
	{
		if (check_strict_2nd_arg(next_tokens, strict_mode) == NG_G)
			return (NG_G);
	}
	if (is_in(NG_NEXT_TO_O_TEXT, get_token(*next_tokens)))
		return (NG_G);
	if (subshell_depth == 0 && get_token(*next_tokens)->type == OP_CLOSE)
		return (NG_G);
	return (OK_G);
}
