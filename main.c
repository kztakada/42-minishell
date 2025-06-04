/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/06/04 15:34:33 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "for_test_print.h"
#include "minishell.h"
#include "signal_for_minishell.h"

static t_bool	safe_add_history(char *input, t_env env)
{
	if (input == NULL)
		return (ft_putstr_fd(EXIT_PROMPT, STDOUT_FILENO), rl_clear_history(),
			exit(*(env.exit_status)), FALSE);
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

static void	execute_command(char *input, t_env env)
{
	t_list			*token_list;
	t_abs_node		*abs_tree;
	t_exit_status	result;

	// TODO: lexerでエラーした時にexit_statusは何番を返せば良いか？
	token_list = NULL;
	result = lexer(input, &token_list);
	free(input);
	if (result != 0)
	{
		*(env.exit_status) = result;
		return ;
	}
	// print_token_list(token_list); // テスト用
	abs_tree = NULL;
	result = parser(token_list, &abs_tree, env);
	ft_lstclear(&token_list, free_token);
	if (result != 0)
	{
		*(env.exit_status) = result;
		return ;
	}
	// 空文字入力など、exec_が実行されない場合は、exit_statusを更新しないこと
	exec(abs_tree, &env);
	// printf("exit status: %d\n", exit_status); // テスト用
	free_abs_tree(abs_tree);
}

void	reset_signal(t_env env)
{
	if (g_sig != 0)
	{
		*(env.exit_status) = g_sig + EXIT_S_INVALID_ARG;
		g_sig = 0;
	}
}

void	dialog_minishell(t_env env)
{
	char	*input;

	rl_event_hook = nop_event_hook;
	while (TRUE)
	{
		set_sig_handlers_in_dialog();
		input = readline(PROMPT);
		reset_signal(env);
		if (safe_add_history(input, env) == FALSE)
			continue ;
		execute_command(input, env);
	}
}

void	exec_minishell(t_env env)
{
	char	*input;
	char	*newline;

	input = NULL;
	input = get_next_line(STDIN_FILENO);
	while (input != NULL)
	{
		// 複数行処理やめて、１行の未処理対応にするか検討すること
		newline = ft_strchr(input, '\n'); // TODO: 複数行実行した場合、出力パイプがどうなるか確認
		if (newline)
			*newline = '\0';
		*(env.line_count) += 1;
		// printf("%s\n", input); // テスト用
		execute_command(input, env);
		input = get_next_line(STDIN_FILENO);
	}
	free(input);
}

void	minishell(t_env env)
{
	const int	is_interactive = isatty(STDIN_FILENO);

	// print_env_list(env_vars); // テスト用
	rl_outstream = stderr;
	if (is_interactive)
		dialog_minishell(env);
	else
		exec_minishell(env);
	ft_lstclear(&(env.env_vars), free_env_var);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	static t_exit_status	exit_status = 0;
	t_bool					unset_oldpwd;
	t_env					env;
	int						line_count;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd(TOO_MANY_ARGS, STDERR_FILENO), EXIT_FAILURE);
	env.env_vars = init_envlst(envp);
	if (env.env_vars == NULL)
		return (perror(ERROR_MALLOC), EXIT_FAILURE);
	env.exit_status = &exit_status;
	unset_oldpwd = FALSE;
	env.unset_oldpwd = &unset_oldpwd;
	line_count = 0;
	env.line_count = &line_count;
	minishell(env);
	return (exit_status);
}
