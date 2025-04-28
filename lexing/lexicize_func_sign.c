/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicize_func_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:10:29 by katakada          #+#    #+#             */
/*   Updated: 2025/04/28 20:32:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

static t_list	*get_listable_token(t_token *token, t_list **token_list)
{
	t_list			*listable_token;
	unsigned int	token_id;

	if (*token_list == NULL)
		token_id = 0;
	else
	{
		token_id = ((t_token *)(ft_lstlast(*token_list)->content))->id;
		if (token_id == UINT_MAX)
			return (perror("Token ID overflow"), NULL);
		else
			token_id++;
	}
	token->id = token_id;
	listable_token = ft_lstnew(token);
	if (listable_token == NULL)
		return (perror(ERROR_MALLOC), NULL);
	return (listable_token);
}

int	add_token_to_list(t_token *token, t_list **token_list)
{
	t_list	*listable_token;
	int		lexicized_size;

	listable_token = get_listable_token(token, token_list);
	if (listable_token == NULL)
		return (FAILURE);
	ft_lstadd_back(token_list, listable_token);
	lexicized_size = ft_strlen(token->value);
	return (lexicized_size);
}

static t_token	*get_func_token(char *input)
{
	t_token	*allocated_token;

	if (!input || !*input)
		return (NULL);
	allocated_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (allocated_token == NULL)
		return (perror(ERROR_MALLOC), NULL);
	allocated_token->type = (t_token_type)lookup_dict(input,
			TOKEN_TYPE_DICT).d_index;
	allocated_token->value = get_dict_word(allocated_token->type,
			TOKEN_TYPE_DICT);
	if (allocated_token->value == NULL)
	{
		free(allocated_token);
		return (perror(ERROR_MALLOC), NULL);
	}
	return (allocated_token);
}

int	lexicize_func_sign(char *input, t_list **token_list)
{
	t_token	*token;
	int		lexicized_size;

	if (!input || !*input)
		return (FAILURE);
	token = get_func_token(input);
	if (token == NULL)
		return (FAILURE);
	lexicized_size = add_token_to_list(token, token_list);
	if (lexicized_size == FAILURE)
	{
		free_token(token);
		return (FAILURE);
	}
	return (lexicized_size);
}

int	append_terminator(t_list **token_list)
{
	t_token	*terminator_token;
	int		lexicized_size;

	terminator_token = get_func_token("\n");
	if (terminator_token == NULL)
		return (FAILURE);
	lexicized_size = add_token_to_list(terminator_token, token_list);
	if (lexicized_size == FAILURE)
	{
		free_token(terminator_token);
		return (FAILURE);
	}
	return (lexicized_size);
}
