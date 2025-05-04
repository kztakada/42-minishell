/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/04 23:44:30 by katakada         ###   ########.fr       */
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

static void	put_quoted_content(t_list *token_list)
{
	t_token	*first_token;
	t_token	*second_token;
	t_token	*third_token;

	if (token_list == NULL)
		return ;
	if (token_list->next == NULL)
		return ;
	if (token_list->next->next == NULL)
		return ;
	first_token = (t_token *)(token_list->content);
	second_token = (t_token *)(token_list->next->content);
	third_token = (t_token *)(token_list->next->next->content);
	if (second_token->type == OPERAND_TEXT
		&& first_token->type == third_token->type)
	{
		ft_putstr_fd(second_token->value, STDERR_FILENO);
		ft_putstr_fd(third_token->value, STDERR_FILENO);
	}
}

static void	put_quoted_syntax_err(t_list *token_list)
{
	t_token	*first_token;

	if (token_list == NULL)
		return ;
	first_token = (t_token *)(token_list->content);
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(first_token->value, STDERR_FILENO);
	put_quoted_content(token_list);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

static void	put_syntax_err(t_list *token_list)
{
	char	*err_token;
	t_token	*token;

	token = (t_token *)(token_list->content);
	if (!token)
		return ;
	if (token->type == QUOTE_DOUBLE || token->type == QUOTE_SINGLE)
	{
		put_quoted_syntax_err(token_list);
		return ;
	}
	if (token->type == TERMINATOR)
		err_token = "newline";
	else if (token->type == OPERAND_TEXT)
		err_token = replase_first_ifs_with_null(token->value);
	else
		err_token = token->value;
	ft_putstr_fd(ERROR_SYNTAX, STDERR_FILENO);
	ft_putstr_fd(err_token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

t_exit_status	parse(t_list *token_list, t_list **abs_tree)
{
	int	subshell_count;
	int	result;

	subshell_count = 0;
	if (token_list == NULL)
		return (EXIT_S_FAILURE);
	// printf("subshell_count: %d\n", subshell_count);
	while (token_list)
	{
		result = check_tokens_grammar(&token_list, &subshell_count);
		// printf("result: %d  subshell_count: %d\n", result, subshell_count);
		if (result == NG)
			return (put_syntax_err(token_list), EXIT_S_SYNTAX_ERROR);
		if (((t_token *)(token_list->content))->type == TERMINATOR)
			break ;
	}
	*abs_tree = ft_lstnew(NULL);
	if (abs_tree == NULL)
		return (EXIT_S_FAILURE);
	return (EXIT_S_SUCCESS);
}
