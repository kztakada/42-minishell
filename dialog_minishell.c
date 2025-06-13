/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dialog_minishell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 21:28:21 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 21:32:27 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal_for_minishell.h"

void	execute_command(char *input, t_env env)
{
	t_exit_status	result;

	result = lexer(input, &(env.token_list));
	free(input);
	if (result != 0)
	{
		*(env.exit_status) = result;
		return ;
	}
	// print_token_list(token_list); // テスト用
	result = parser(env.token_list, &(env.abs_tree), env);
	ft_lstclear(&(env.token_list), free_token);
	if (result != 0)
	{
		*(env.exit_status) = result;
		return ;
	}
	exec(&env);
	// printf("exit status: %d\n", exit_status); // テスト用
	free_abs_tree(env.abs_tree);
}

static void	reset_g_sig(t_env env)
{
	if (g_sig != 0)
	{
		*(env.exit_status) = g_sig + EXIT_S_INVALID_ARG;
		g_sig = 0;
	}
}

static t_bool	safe_add_history(char *input, t_env env)
{
	if (input == NULL)
	{
		ft_putstr_fd(EXIT_PROMPT, STDERR_FILENO);
		return (free_all_env(env), exit(*(env.exit_status)), FALSE);
	}
	if (*input)
		add_history(input);
	else
	{
		free(input);
		return (FALSE);
	}
	*(env.line_count) += 1;
	return (TRUE);
}

void	dialog_minishell(t_env env)
{
	char	*input;

	rl_outstream = stderr;
	rl_event_hook = nop_event_hook;
	while (TRUE)
	{
		set_sig_handlers_in_dialog();
		input = readline(PROMPT);
		reset_g_sig(env);
		if (safe_add_history(input, env) == FALSE)
			continue ;
		execute_command(input, env);
	}
}
