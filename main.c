/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 21:31:27 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "for_test_print.h"
#include "minishell.h"

void	exec_minishell(t_env env)
{
	char	*input;
	char	*end_of_line;

	input = get_next_line(STDIN_FILENO);
	if (input == NULL)
		return (perror(ERROR_STDREAD), free_all_env(env), exit(EXIT_S_FAILURE));
	end_of_line = ft_strchr(input, '\n');
	if (!end_of_line)
		return (perror(ERROR_STDREAD), free_all_env(env), exit(EXIT_S_FAILURE));
	*end_of_line = '\0';
	while (end_of_line)
	{
		end_of_line = get_next_line(STDIN_FILENO);
		free(end_of_line);
	}
	*(env.line_count) += 1;
	execute_command(input, env);
	free_all_env(env);
	exit(*(env.exit_status));
}

void	minishell(t_env env)
{
	const int	is_interactive = isatty(STDIN_FILENO);

	// print_env_list(env_vars); // テスト用
	if (is_interactive)
		dialog_minishell(env);
	else
		exec_minishell(env);
	free_all_env(env);
}

int	main(int argc, char **argv, char **envp)
{
	t_env					env;
	static t_exit_status	exit_status = 0;
	t_bool					unset_oldpwd;
	int						line_count;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd(TOO_MANY_ARGS, STDERR_FILENO);
		return (EXIT_S_FAILURE);
	}
	unset_oldpwd = FALSE;
	line_count = 0;
	env.exit_status = &exit_status;
	env.unset_oldpwd = &unset_oldpwd;
	env.line_count = &line_count;
	env.env_vars = init_envlst(envp);
	if (env.env_vars == NULL)
		return (EXIT_S_FAILURE);
	env.token_list = NULL;
	env.abs_tree = NULL;
	minishell(env);
	return (exit_status);
}
