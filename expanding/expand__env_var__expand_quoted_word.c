/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var__expand_quoted_word.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:56:19 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 19:36:21 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

t_list	*expand_single_quoted_word(char *str)
{
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	if (str == NULL)
		return (NULL);
	expanded_token = init_expanding_token(ET_QUOTED_STR);
	if (expanded_token == NULL)
		return (NULL);
	expanding_token = (t_expanding_token *)expanded_token->content;
	expanding_token->str = ft_strdup(str);
	if (expanding_token->str == NULL)
		return (ft_lstclear(&expanded_token, free_expanding_token), NULL);
	return (expanded_token);
}

t_list	*expand_double_quoted_word(char *to_expand, t_env env)
{
	char				*d_quoted_str;
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	d_quoted_str = ft_strdup("");
	if (d_quoted_str == NULL)
		return (perror(ERROR_MALLOC), NULL);
	while (*to_expand != '\0')
	{
		if (*to_expand == '$')
			d_quoted_str = strjoin_free(d_quoted_str, expand_dollar(&to_expand,
						env));
		else
			d_quoted_str = strjoin_free(d_quoted_str,
					use_raw_str_when_double_quoted(&to_expand));
		if (d_quoted_str == NULL)
			return (ft_lstclear(&expanded_token, free_expanding_token), NULL);
	}
	expanded_token = init_expanding_token(ET_QUOTED_STR);
	if (expanded_token == NULL)
		return (free(d_quoted_str), ft_lstclear(&expanded_token,
				free_expanding_token), NULL);
	expanding_token = (t_expanding_token *)expanded_token->content;
	expanding_token->str = d_quoted_str;
	return (expanded_token);
}
