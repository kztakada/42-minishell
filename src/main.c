/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/04/05 17:34:08 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"
int	sum(int a, int b)
{
	return (a + b);
}

int	app_main(void)
{
	char	*input;

	// t_token			*tokens;
	// t_parse_error	*error;
	// t_node			*as_tree;
	while (TRUE)
	{
		input = readline(PROMPT);
		if (input == NULL)
			exit(EXIT_FAILURE);
		printf("%s\n", input);
		free(input);
		// if (*input)
		// 	add_history(input);
		// tokens = tokenize(input); //未実装
		// if (tokens == NULL)
		// {
		// 	free(input);
		// 	continue ;
		// }
		// error = parse(tokens, &as_tree); //未実装
		// if (error->code != PARSE_NO_ERROR)
		// {
		// 	handle_parse_error(error); //未実装
		// 	free(input);
		// 	free(tokens);
		// 	free(error);
		// 	continue ;
		// }
		// exec_(as_tree);                          //未実装
		// all_free(input, tokens, error, as_tree); //未実装
	}
	return (0);
}

#ifndef TEST

int	main(void)
{
	return (app_main());
}
#endif // TEST