/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:50:07 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 18:06:18 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "for_test_parsing.h"
#include "parsing.h"

static char	*e_handle_expand_env(char **input, t_env env)
{
	char	*var_name;
	char	*var_value;
	int		i;

	if (*input == NULL)
		return (NULL);
	if (**input == '?')
	{
		var_value = ft_itoa((int)(*env.exit_status));
		if (var_value == NULL)
			return (exit(EXIT_FAILURE), NULL);
		(*input)++;
		return (var_value);
	}
	var_name = ft_strdup(*input);
	if (var_name == NULL)
		return (exit(EXIT_FAILURE), NULL);
	i = 0;
	while (var_name[i] != '\0' && !is_ifs(var_name[i]))
		i++;
	*input = *input + i;
	if (is_ifs(var_name[i]))
		var_name[i] = '\0';
	var_value = get_envlst_val(var_name, env.env_vars);
	return (free(var_name), var_value);
}

static char	*expand_heredoc(char *to_expand, t_env env)
{
	char	*origin;
	char	*expanded;
	int		plain_str_len;

	origin = to_expand;
	expanded = NULL;
	while (*to_expand != '\0')
	{
		if (*to_expand == '$')
		{
			to_expand++;
			expanded = e_handle_strjoin_free(expanded,
					e_handle_expand_env(&to_expand, env));
		}
		else
		{
			plain_str_len = 0;
			while (to_expand[plain_str_len] != '\0'
				&& to_expand[plain_str_len] != '$')
				plain_str_len++;
			expanded = e_handle_strjoin_free(expanded,
					e_handle_substr(to_expand, plain_str_len));
			to_expand = to_expand + plain_str_len;
		}
	}
	free(origin);
	return (expanded);
}

static void	heredoc_child_process(int fd, char *eof, t_bool is_quote, t_env env)
{
	char	*input;

	// signal(SIGINT, SIG_DFL);
	while (TRUE)
	{
		input = readline("> ");
		if (input == NULL)
			break ;
		if (ft_strcmp(input, eof) == 0)
			break ;
		if (is_quote == FALSE)
			input = expand_heredoc(input, env);
		if (input == NULL)
			exit(EXIT_FAILURE);
		ft_putstr_fd(input, fd);
		ft_putstr_fd("\n", fd);
	}
	if (input != NULL)
		free(input);
	exit(EXIT_SUCCESS);
}

static int	parse_heredoc(char *eof, t_bool is_quote, t_env env)
{
	int	p[2];
	int	pid;

	pipe(p);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		heredoc_child_process(p[1], eof, is_quote, env);
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
	t_list			*current;
	t_list			*file_name_words;
	char			*delimiter;
	t_redirection	*redirection;
	t_binary_result	result;

	result = SUCCESS_BIN_R;
	current = parsing_state->heredoc_list;
	while (current && result == SUCCESS_BIN_R)
	{
		if (current->content != NULL)
		{
			redirection = (t_redirection *)current->content;
			file_name_words = redirection->file_name_words;
			delimiter = get_heredoc_delimiter(file_name_words);
			redirection->expanded_file_name = delimiter;
			redirection->fd = parse_heredoc(delimiter,
					has_quoted_text(redirection->file_name_words), env);
			if (redirection->fd < 0)
				result = FAILURE_BIN_R;
			// all_get_line(redirection->fd); //テスト用
		}
		current = current->next;
	}
	ft_lstclear(&(parsing_state->heredoc_list), no_del);
	return (result);
}
