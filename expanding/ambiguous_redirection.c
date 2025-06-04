/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambiguous_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:11:14 by katakada          #+#    #+#             */
/*   Updated: 2025/06/03 20:59:06 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static t_bool	is_existing_arg(t_list **expanding_tokens)
{
	if (*expanding_tokens == NULL)
		return (FALSE);
	if (get_ex_token(expanding_tokens)->type == ET_SEPARATOR)
		return (FALSE);
	if (get_ex_token(expanding_tokens)->type == ET_UNQUOTED_STR)
	{
		if (get_ex_token(expanding_tokens)->str == NULL)
			return (FALSE);
		if (ft_strcmp(get_ex_token(expanding_tokens)->str, "") == 0)
			return (FALSE);
	}
	return (TRUE);
}

static int	get_existing_arg_size(t_list *expanding_tokens)
{
	t_list	*current_token;
	int		arg_count;

	arg_count = 0;
	if (expanding_tokens == NULL)
		return (arg_count);
	if (is_existing_arg(&expanding_tokens))
		arg_count++;
	current_token = expanding_tokens;
	while (current_token != NULL)
	{
		to_next_separate_top(&current_token);
		if (current_token == NULL)
			break ;
		if (is_existing_arg(&current_token))
			arg_count++;
	}
	return (arg_count);
}

t_bool	is_ambiguous_redirection(t_list *expanding_tokens)
{
	int	arg_count;

	arg_count = get_existing_arg_size(expanding_tokens);
	if (arg_count == 0)
		return (TRUE);
	if (arg_count == 1)
		return (FALSE);
	else
		return (TRUE);
}

void	put_ambiguous_redirection_err(t_list *file_name_words)
{
	t_list			*current_word;
	t_parsed_word	*parsed_word;

	if (file_name_words == NULL)
		return ;
	current_word = file_name_words;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	while (current_word != NULL)
	{
		parsed_word = (t_parsed_word *)current_word->content;
		if (parsed_word->type == W_SINGLE_QUOTED)
			ft_putstr_fd("'", STDERR_FILENO);
		else if (parsed_word->type == W_DOUBLE_QUOTED)
			ft_putstr_fd("\"", STDERR_FILENO);
		ft_putstr_fd(parsed_word->str, STDERR_FILENO);
		if (parsed_word->type == W_SINGLE_QUOTED)
			ft_putstr_fd("'", STDERR_FILENO);
		else if (parsed_word->type == W_DOUBLE_QUOTED)
			ft_putstr_fd("\"", STDERR_FILENO);
		current_word = current_word->next;
	}
	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
}
