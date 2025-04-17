/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/04/18 00:25:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
int	sum(int a, int b)
{
	return (a + b);
}

// void	all_free(char *input, t_token *tokens, t_node *as_tree)
// {
// 	if (input)
// 		free(input);
// 	if (tokens)
// 		free(tokens);
// 	if (as_tree)
// 		free(as_tree);
// }
// void	handle_parse_error(t_parse_error error)
// {
// 	if (error.code == E_MEM)
// 	{
// 		fprintf(stderr, "Memory allocation error\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (error.code == E_SYNTAX)
// 	{
// 		fprintf(stderr, "Syntax error\n");
// 		exit(EXIT_FAILURE);
// 	}
// }

// トークナイザーの出力テスト用
void	print_token_list(t_list *token_list)
{
	t_list	*current;
	t_token	*token;

	current = token_list;
	while (current)
	{
		token = (t_token *)current->content;
		printf("Token type: %d, content: %s\n", token->type, token->content);
		current = current->next;
	}
}

int	app_main(void)
{
	char	*input;
	t_list	*token_list;

	// t_parse_error	error;
	// t_node			*as_tree;
	while (TRUE)
	{
		input = readline(PROMPT);
		if (input == NULL)
			exit(EXIT_FAILURE);
		if (*input)
			add_history(input);
		token_list = tokenize(input);
		if (token_list == NULL)
		{
			free(input);
			continue ;
		}
		print_token_list(token_list);
		ft_lstclear(&token_list, delete_token);
		// as_tree = parse(tokens, &error); //未実装
		// if (error.code != PARSE_NO_ERROR)
		// {
		// 	handle_parse_error(error); //未実装
		// 	free(input);
		// 	free(tokens);
		// 	continue ;
		// }
		// printf("as_tree->args: %s\n", as_tree->args);
		// // exec_(as_tree); //未実装
		// all_free(input, tokens, as_tree);
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