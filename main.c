/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:53:45 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

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

static int	execute_command(char *input, t_list *env_lists)
{
	t_list					*token_list;
	t_abs_node				*abs_tree;
	static t_exit_status	exit_status = 0;
	t_env					env;

	// TODO: lexerでエラーした時にexit_statusは何番を返せば良いか？
	env.env_lists = env_lists;
	env.exit_status = &exit_status;
	token_list = NULL;
	exit_status = lexer(input, &token_list);
	free(input);
	if (exit_status != 0)
		return (FAILURE);
	// print_token_list(token_list); // テスト用
	abs_tree = NULL;
	exit_status = parser(token_list, &abs_tree, env);
	ft_lstclear(&token_list, free_token);
	if (exit_status != 0)
		return (FAILURE);
	// exit_status = expander(abs_tree, env);
	// exit_status = exec_(abs_tree, env_lists, exit_status); //未実装
	free_abs_tree(abs_tree);
	return (SUCCESS);
}

int	app_main(int argc, char **argv, char **env)
{
	const int	is_interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	char		*input;
	char		*newline;
	t_list		*env_lists;

	(void)argc;
	(void)argv;
	env_lists = init_envlst(env);
	// print_env_list(env_lists); // テスト用
	if (is_interactive)
	{
		while (TRUE)
		{
			input = readline(PROMPT);
			if (safe_add_history(input) == FALSE)
				continue ;
			execute_command(input, env_lists);
		}
	}
	else
	{
		input = NULL;
		input = get_next_line(STDIN_FILENO);
		// TODO: 複数行実行した場合、出力パイプがどうなるか確認
		// 複数行処理やめて、１行の未処理対応にするか検討すること
		while (input != NULL)
		{
			newline = ft_strchr(input, '\n');
			if (newline)
				*newline = '\0';
			// printf("%s\n", input); // テスト用
			execute_command(input, env_lists);
			input = get_next_line(STDIN_FILENO);
		}
		free(input);
	}
	ft_lstclear(&env_lists, free_env_var);
	return (0);
}

#ifndef TEST

int	main(int argc, char **argv, char **env)
{
	return (app_main(argc, argv, env));
}
#endif // TEST