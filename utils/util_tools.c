/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:47:55 by katakada          #+#    #+#             */
/*   Updated: 2025/05/19 21:48:00 by katakada         ###   ########.fr       */
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
