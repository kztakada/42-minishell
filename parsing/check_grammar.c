/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_grammar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:09:41 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 23:03:16 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static char	*replase_first_ifs_with_null(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_ifs(str[i]))
		{
			str[i] = '\0';
			break ;
		}
		i++;
	}
	return (str);
}

static void	put_syntax_err(t_token *token)
{
	char	*err_token;

	if (!token)
		return ;
	if (token->type == TERMINATOR)
		err_token = "newline";
	else if (token->type == OPERAND_TEXT)
		err_token = replase_first_ifs_with_null(token->value);
	else
		err_token = token->value;
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(err_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static int	check_prefix_grammar(t_token *testing_token)
{
	if (can_use_as_first_token(testing_token) == FALSE)
		return (put_syntax_err(testing_token), NG);
	return (OK);
}

static t_bool	is_in(t_token *testing_token, char *dict)
{
	return (lookup_dict(testing_token->value, dict).in_d);
}

static int	check_following_grammar(t_token *testing_token)
{
	if (is_in(testing_token, REDIRECT_OP))
		return (check_following_redirect(testing_token));
	else if (is_in(testing_token, SUBSHELL_OP))
		return (check_following_subshell(testing_token));
	else if (is_in(testing_token, BINARY_OP_PIPE))
		return (check_following_binop_pipe(testing_token));
	else
		return (check_following_text(testing_token));
}

int	check_tokens_grammar(t_list *token_list)
{
	t_list	*current_list_pos;

	if (token_list == NULL)
		return (NG);
	current_list_pos = token_list;
	if (check_prefix_grammar(get_token(current_list_pos)) == NG)
		return (NG);
	while (current_list_pos)
	{
		if (check_following_grammar(get_token(current_list_pos)) == NG)
			return (NG);
		forward_token_list(&current_list_pos);
	}
	return (OK);
}
