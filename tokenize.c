/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:47:32 by katakada          #+#    #+#             */
/*   Updated: 2025/04/18 20:02:13 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static int	is_space(char c)
{
	if (lookup_dict(&c, SPACE_DICT).in_d)
		return (TRUE);
	return (FALSE);
}

static int	is_operator(char *str)
{
	if (lookup_dict(str, OPERATORS_DICT).in_d)
		return (TRUE);
	return (FALSE);
}

static t_list	*get_new_listable_token(t_token_type token_type,
		char *token_content)
{
	t_token	*new_token;
	t_list	*new_listable_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (perror(ERROR_MALLOC), NULL);
	new_token->type = token_type;
	new_token->content = token_content;
	new_listable_token = ft_lstnew(new_token);
	if (!new_listable_token)
	{
		free(new_token);
		return (perror(ERROR_MALLOC), NULL);
	}
	return (new_listable_token);
}

int	add_operator_token_to_list(char *input, t_list **token_list)
{
	t_list	*new_listable_token;
	int		token_type;
	char	*token_content;

	if (!input || !*input)
		return (FAILURE);
	token_type = lookup_dict(input, OPERATORS_DICT).d_index;
	token_content = get_dict_word(token_type, OPERATORS_DICT);
	new_listable_token = get_new_listable_token(token_type, token_content);
	if (!new_listable_token)
		return (FAILURE);
	ft_lstadd_back(token_list, new_listable_token);
	return (ft_strlen(token_content));
}

int	get_operand_len(char *input)
{
	int	operand_len;

	operand_len = 0;
	while (input[operand_len] && !is_operator(input + operand_len))
	{
		operand_len++;
	}
	return (operand_len);
}

int	add_operand_token_to_list(char *input, t_list **token_list)
{
	t_list	*new_listable_token;
	char	*token_content;
	int		token_content_len;

	if (!input || !*input)
		return (FAILURE);
	token_content_len = get_operand_len(input);
	token_content = ft_substr(input, 0, token_content_len);
	if (!token_content)
		return (perror(ERROR_MALLOC), FAILURE);
	new_listable_token = get_new_listable_token(OPERAND_TEXT, token_content);
	if (!new_listable_token)
	{
		free(token_content);
		return (FAILURE);
	}
	ft_lstadd_back(token_list, new_listable_token);
	return (token_content_len);
}

void	delete_token(void *target)
{
	t_token	*token;

	token = (t_token *)target;
	if (token)
	{
		free(token->content);
		free(token);
	}
}

// Noted: operand is the string sandwiched between operators
t_list	*tokenize(char *input)
{
	t_list	*token_list;
	int		append_len;

	token_list = NULL;
	append_len = 0;
	while (*input)
	{
		if (is_space(*input))
			input++;
		else if (is_operator(input))
		{
			append_len = add_operator_token_to_list(input, &token_list);
			if (append_len == FAILURE)
				return (ft_lstclear(&token_list, delete_token), NULL);
			input += append_len;
		}
		else
		{
			append_len = add_operand_token_to_list(input, &token_list);
			if (append_len == FAILURE)
				return (ft_lstclear(&token_list, delete_token), NULL);
			input += append_len;
		}
	}
	return (token_list);
}
