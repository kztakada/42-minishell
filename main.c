/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/04/22 18:40:18 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

// トークナイザーの出力テスト用
// void	print_token_list(t_list *token_list)
// {
// 	t_list	*current;
// 	t_token	*token;

// 	current = token_list;
// 	while (current)
// 	{
// 		token = (t_token *)current->content;
// 		printf("Token type: %d, content: %s\n", token->type, token->content);
// 		current = current->next;
// 	}
// }

static t_bool	safe_add_history(char *input)
{
	if (input == NULL)
		return (exit(EXIT_FAILURE), FALSE);
	if (*input)
		add_history(input);
	else
	{
		free(input);
		return (FALSE);
	}
	return (TRUE);
}

int	app_main(void)
{
	char		*input;
	t_list		*token_list;
	t_abs_node	*abs_tree;

	while (TRUE)
	{
		input = readline(PROMPT);
		if (safe_add_history(input) == FALSE)
			continue ;
		token_list = lexer(input);
		free(input);
		if (token_list == NULL)
			continue ;
		// print_token_list(token_list);
		abs_tree = parse(token_list); //未実装
		ft_lstclear(&token_list, delete_token);
		if (abs_tree == NULL)
			continue ;
		exec_(abs_tree); //未実装
	}
	return (0);
}

#ifndef TEST

int	main(void)
{
	// t_dict_out	d_out;
	// d_out = lookup_dict("<<", OPERATORS_DICT);
	// printf("in_d: %d\n", d_out.in_d);
	// printf("d_index: %d\n", d_out.d_index);
	// printf("nx_str: %s\n", d_out.nx_str);
	// printf("error: %s\n", d_out.error);
	// d_out = lookup_dict("&&", OPERATORS_DICT);
	// printf("in_d: %d\n", d_out.in_d);
	// printf("d_index: %d\n", d_out.d_index);
	// printf("nx_str: %s\n", d_out.nx_str);
	// printf("error: %s\n", d_out.error);
	// return (0);
	return (app_main());
}
#endif // TEST