/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:50:07 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 21:39:38 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "parsing.h"
#include "signal_for_minishell.h"

static char	*expand_heredoc_input(char *to_expand, t_env env)
{
	char	*origin;
	char	*expanded_str;

	origin = to_expand;
	expanded_str = ft_strdup("");
	if (expanded_str == NULL)
		return (perror(ERROR_MALLOC), free_all_env(env), exit(EXIT_S_FAILURE),
			NULL);
	while (*to_expand != '\0')
	{
		if (*to_expand == '$')
			expanded_str = strjoin_free(expanded_str, expand_dollar(&to_expand,
						env));
		else
			expanded_str = strjoin_free(expanded_str,
					use_raw_str_when_double_quoted(&to_expand));
		if (expanded_str == NULL)
			return (free(origin), free_all_env(env), exit(EXIT_S_FAILURE),
				NULL);
	}
	free(origin);
	return (expanded_str);
}

static void	ask_heredoc_child_process(int fd, char *eof, t_bool is_quote,
		t_env env)
{
	char	*input;

	if (!isatty(STDIN_FILENO))
		return (exit_warning_for_heredoc(env, eof));
	while (TRUE)
	{
		input = readline(HEREDOC_PROMPT);
		if (g_sig == SIGINT)
			return (free(input), free_all_env(env), exit(128 + SIGINT));
		if (input == NULL)
			return (free(input), exit_warning_for_heredoc(env, eof));
		if (ft_strcmp(input, eof) == 0)
			break ;
		if (!is_quote)
			input = expand_heredoc_input(input, env);
		if (input == NULL)
			return (free_all_env(env), exit(EXIT_S_FAILURE));
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
		free(input);
	}
	if (input != NULL)
		free(input);
	free_all_env(env);
	exit(EXIT_S_SUCCESS);
}

static int	ask_user_for_heredoc(char *eof, t_bool is_quote, t_env env,
		t_parsing_state *parsing_state)
{
	int	p[2];
	int	pid;

	pipe(p);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		ft_lstclear(&(parsing_state->heredoc_list), no_del);
		env.abs_tree = *(parsing_state->tree_top_node);
		ask_heredoc_child_process(p[1], eof, is_quote, env);
	}
	else
	{
		waitpid(pid, &pid, 0);
		close(p[1]);
		if (WIFEXITED(pid) == FALSE)
			return (WEXITSTATUS(pid) * -1);
		if (WEXITSTATUS(pid) == 128 + SIGINT)
			return (-130);
		if (WEXITSTATUS(pid) == EXIT_S_FAILURE)
			return (-1);
	}
	return (p[0]);
}

static t_parsing	exec_heredoc(t_redirection *redirection,
		t_parsing_state *parsing_state, t_env env)
{
	t_list	*file_name_words;
	char	*eof_str;

	file_name_words = redirection->file_name_words;
	eof_str = get_heredoc_delimiter(file_name_words);
	redirection->expanded_file_name = eof_str;
	redirection->fd = ask_user_for_heredoc(eof_str,
			has_quoted_text(redirection->file_name_words), env, parsing_state);
	if (redirection->fd < 0)
		return ((redirection->fd) * -1);
	return (SUCCESS_P);
}

t_parsing	call_heredoc(t_parsing_state *parsing_state, t_env env)
{
	t_list			*current_heredoc;
	t_redirection	*redirection;
	t_parsing		result;

	result = SUCCESS_P;
	current_heredoc = parsing_state->heredoc_list;
	while (current_heredoc && result == SUCCESS_P)
	{
		if (current_heredoc->content != NULL)
		{
			redirection = (t_redirection *)current_heredoc->content;
			result = exec_heredoc(redirection, parsing_state, env);
		}
		current_heredoc = current_heredoc->next;
	}
	ft_lstclear(&(parsing_state->heredoc_list), no_del);
	return (result);
}
