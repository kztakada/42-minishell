/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 23:39:23 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

void	free_abs_node(void *target)
{
	t_abs_node	*abs_node;

	abs_node = (t_abs_node *)target;
	if (abs_node)
	{
		free(abs_node->cmd_args);
		free(abs_node->expanded_args);
		free(abs_node->token);
		free(abs_node);
	}
}

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

int	parse(t_list *token_list, t_list **abs_tree)
{
	int	subshell_count;

	subshell_count = 0;
	if (token_list == NULL)
		return (EXIT_S_FAILURE);
	if (check_tokens_grammar(&token_list, &subshell_count) == NG)
		return (put_syntax_err(token_list->content), EXIT_S_SYNTAX_ERROR);
	*abs_tree = ft_lstnew(NULL);
	if (abs_tree == NULL)
		return (EXIT_S_FAILURE);
	return (EXIT_S_SUCCESS);
}
