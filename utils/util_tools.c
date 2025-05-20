/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:47:55 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 17:00:58 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	is_ifs(char c)
{
	if (lookup_dict(&c, IFS_DICT).in_d)
		return (TRUE);
	return (FALSE);
}

t_list	**forward_token_list(t_list **current_token_list)
{
	*current_token_list = (*current_token_list)->next;
	return (current_token_list);
}

char	*strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (result == NULL)
		return (NULL);
	free(s1);
	free(s2);
	return (result);
}
