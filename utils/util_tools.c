/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 21:47:55 by katakada          #+#    #+#             */
/*   Updated: 2025/05/25 19:11:44 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		if (s1 != NULL)
			free(s1);
		if (s2 != NULL)
			free(s2);
		return (NULL);
	}
	free(s1);
	free(s2);
	return (result);
}

void	free_str_list_by_size(char **str_list, int str_list_size)
{
	int	i;

	if (str_list == NULL)
		return ;
	i = 0;
	while (i < str_list_size)
	{
		if (str_list[i] != NULL)
			free(str_list[i]);
		i++;
	}
	free(str_list);
}

void	ft_swap(void **a, void **b)
{
	void	*temp;

	if (a == NULL || b == NULL || *a == NULL || *b == NULL)
		return ;
	temp = *a;
	*a = *b;
	*b = temp;
}
