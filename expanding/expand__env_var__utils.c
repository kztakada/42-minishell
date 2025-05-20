/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:53:58 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 16:58:31 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

t_list	*init_expanding_token(t_e_token_type type)
{
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	expanding_token = malloc(sizeof(t_expanding_token));
	if (expanding_token == NULL)
		return (NULL);
	expanding_token->type = type;
	expanding_token->str = NULL;
	expanded_token = ft_lstnew(expanding_token);
	if (expanded_token == NULL)
	{
		free(expanding_token);
		return (NULL);
	}
	return (expanded_token);
}

t_bool	is_valid_env_cahr(char env_char)
{
	if (ft_isalnum(env_char) || env_char == '_')
		return (TRUE);
	return (FALSE);
}

t_bool	is_death_dollar(char *parsed_word_str)
{
	if (parsed_word_str == NULL || *parsed_word_str == '\0')
		return (FALSE);
	if (*parsed_word_str == '$')
	{
		if (is_ifs(*(parsed_word_str + 1)) || *(parsed_word_str + 1) == '\0')
			return (TRUE);
		else if (*(parsed_word_str + 1) != '?'
			&& !is_valid_env_cahr(*(parsed_word_str + 1)))
			return (TRUE);
	}
	return (FALSE);
}
