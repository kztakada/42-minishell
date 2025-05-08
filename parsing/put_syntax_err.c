/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_syntax_err.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:55:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/06 01:42:19 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_bool	could_replase_first_ifs(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_ifs(str[i]))
		{
			str[i] = '\0';
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static t_loop_status	put_quoted_content(t_list **token_list)
{
	if (is_correct_quoting((*token_list)->next, get_token(*token_list)->type))
	{
		ft_putstr_fd(get_token(*token_list)->value, STDERR_FILENO);
		forward_token_list(token_list);
		ft_putstr_fd(get_token(*token_list)->value, STDERR_FILENO);
		forward_token_list(token_list);
		ft_putstr_fd(get_token(*token_list)->value, STDERR_FILENO);
		return (CONTINUE);
	}
	else
	{
		ft_putstr_fd(get_token(*token_list)->value, STDERR_FILENO);
		return (STOP);
	}
}

static t_loop_status	put_text_content(t_list *token_list)
{
	t_bool	token_had_ifs;

	if (is_ifs(get_token(token_list)->value[0]))
		return (STOP);
	else
	{
		token_had_ifs = could_replase_first_ifs(get_token(token_list)->value);
		ft_putstr_fd(get_token(token_list)->value, STDERR_FILENO);
		if (token_had_ifs == TRUE)
			return (STOP);
		else
			return (CONTINUE);
	}
}

static void	put_operand_syntax_err(t_list *token_list)
{
	if (token_list == NULL)
		return ;
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	while (get_token(token_list)->type == OPERAND_TEXT
		|| get_token(token_list)->type == QUOTE_SINGLE
		|| get_token(token_list)->type == QUOTE_DOUBLE)
	{
		if (is_in(QUOTE_DICT, get_token(token_list)))
		{
			if (put_quoted_content(&token_list) == STOP)
				break ;
		}
		else
		{
			if (put_text_content(token_list) == STOP)
				break ;
		}
		token_list = token_list->next;
	}
	ft_putstr_fd("'\n", STDERR_FILENO);
}

void	put_syntax_err(t_list *token_list)
{
	char	*err_token;
	t_token	*token;

	token = (t_token *)(token_list->content);
	if (!token)
		return ;
	if (token->type == QUOTE_DOUBLE || token->type == QUOTE_SINGLE
		|| token->type == OPERAND_TEXT)
	{
		put_operand_syntax_err(token_list);
		return ;
	}
	if (token->type == TERMINATOR)
		err_token = "newline";
	else
		err_token = token->value;
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(err_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}
