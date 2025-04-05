/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:47:32 by katakada          #+#    #+#             */
/*   Updated: 2025/04/05 17:50:46 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

t_token	*tokenize(char *input)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token));
	if (tokens == NULL)
		return (NULL);
	tokens->type = T_IDENTIFIER;
	tokens->str = input;
	tokens->next = NULL;
	return (tokens);
}
