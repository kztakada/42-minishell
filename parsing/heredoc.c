/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:50:07 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 23:48:30 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_print.h"
#include "parsing.h"

static char	*expand_heredoc_input(char *to_expand, t_env env)
{
	char	*origin;
	char	*expanded_str;

	origin = to_expand;
	expanded_str = ft_strdup("");
	if (expanded_str == NULL)
		return (exit(EXIT_FAILURE), NULL);
	while (*to_expand != '\0')
	{
		if (*to_expand == '$')
			expanded_str = strjoin_free(expanded_str, expand_dollar(&to_expand,
						env));
		else
			expanded_str = strjoin_free(expanded_str,
					use_raw_str_when_double_quoted(&to_expand));
		if (expanded_str == NULL)
			return (free(origin), exit(EXIT_FAILURE), NULL);
	}
	free(origin);
	return (expanded_str);
}

static void	ask_heredoc_child_process(int fd, char *eof, t_bool is_quote,
		t_env env)
{
	char	*input;

	// signal(SIGINT, SIG_DFL);
	while (TRUE)
	{
		input = readline(HEREDOC_PROMPT);
		if (input == NULL)
			exit(EXIT_FAILURE);
		if (ft_strcmp(input, eof) == 0)
			break ;
		if (!is_quote)
			input = expand_heredoc_input(input, env);
		if (input == NULL)
			exit(EXIT_FAILURE);
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
	}
	if (input != NULL)
		free(input);
	exit(EXIT_SUCCESS);
}

static int	ask_user_for_heredoc(char *eof, t_bool is_quote, t_env env)
{
	int	p[2];
	int	pid;

	pipe(p);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		ask_heredoc_child_process(p[1], eof, is_quote, env);
	}
	else
	{
		waitpid(pid, &pid, 0);
		close(p[1]);
		if (WIFEXITED(pid) && WEXITSTATUS(pid) == SIGINT)
			return (-1);
	}
	return (p[0]);
}

t_binary_result	call_heredoc(t_parsing_state *parsing_state, t_env env)
{
	t_list			*current_heredoc;
	t_list			*file_name_words;
	char			*eof_str;
	t_redirection	*redirection;
	t_binary_result	result;

	result = SUCCESS_BIN_R;
	current_heredoc = parsing_state->heredoc_list;
	while (current_heredoc && result == SUCCESS_BIN_R)
	{
		if (current_heredoc->content != NULL)
		{
			redirection = (t_redirection *)current_heredoc->content;
			file_name_words = redirection->file_name_words;
			eof_str = get_heredoc_delimiter(file_name_words);
			redirection->expanded_file_name = eof_str;
			redirection->fd = ask_user_for_heredoc(eof_str,
					has_quoted_text(redirection->file_name_words), env);
			if (redirection->fd < 0)
				result = FAILURE_BIN_R;
			// all_get_line(redirection->fd); //テスト用
		}
		current_heredoc = current_heredoc->next;
	}
	ft_lstclear(&(parsing_state->heredoc_list), no_del);
	return (result);
}
