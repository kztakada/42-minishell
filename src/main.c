/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/04/05 18:08:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
int	sum(int a, int b)
{
	return (a + b);
}

void	all_free(char *input, t_token *tokens, t_node *as_tree)
{
	if (input)
		free(input);
	if (tokens)
		free(tokens);
	if (as_tree)
		free(as_tree);
}
void	handle_parse_error(t_parse_error error)
{
	if (error.code == E_MEM)
	{
		fprintf(stderr, "Memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	else if (error.code == E_SYNTAX)
	{
		fprintf(stderr, "Syntax error\n");
		exit(EXIT_FAILURE);
	}
}

int	app_main(void)
{
	char			*input;
	t_token			*tokens;
	t_parse_error	error;
	t_node			*as_tree;

	while (TRUE)
	{
		input = readline(PROMPT);
		if (input == NULL)
			exit(EXIT_FAILURE);
		if (*input)
			add_history(input);
		tokens = tokenize(input); //未実装
		if (tokens == NULL)
		{
			free(input);
			continue ;
		}
		// printf("%s\n", tokens->str);
		as_tree = parse(tokens, &error); //未実装
		if (error.code != PARSE_NO_ERROR)
		{
			handle_parse_error(error); //未実装
			free(input);
			free(tokens);
			continue ;
		}
		printf("as_tree->args: %s\n", as_tree->args);
		// exec_(as_tree); //未実装
		all_free(input, tokens, as_tree);
	}
	return (0);
}

#ifndef TEST

int	main(void)
{
	return (app_main());
}
#endif // TEST