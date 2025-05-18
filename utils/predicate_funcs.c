/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   predicate_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:07:33 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 15:08:26 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

int	is_ifs(char c)
{
	if (lookup_dict(&c, IFS_DICT).in_d)
		return (TRUE);
	return (FALSE);
}
