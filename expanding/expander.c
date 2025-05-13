/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:57:12 by katakada          #+#    #+#             */
/*   Updated: 2025/05/13 19:58:34 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

char	*get_envlst_val(char *name, t_list *envlst)
{
	t_env_var	*env_var;

	while (envlst)
	{
		env_var = (t_env_var *)envlst->content;
		if (ft_strcmp(name, (env_var->name)) == 0)
			return (env_var->value);
		envlst = envlst->next;
	}
	return (NULL);
}
