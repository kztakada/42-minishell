/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/06 00:56:00 by katakada         ###   ########.fr       */
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
