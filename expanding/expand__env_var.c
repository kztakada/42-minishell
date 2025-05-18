/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:06:51 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 21:06:20 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

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

// 未実装
t_list	*expand_env_var_with_expanding_tokens(t_list *parsed_words, t_env env)
{
	t_list	*expanding_tokens;
	t_list	*current;
	char	*expanded_str;

	(void)env;
	expanding_tokens = NULL;
	current = parsed_words;
	while (current != NULL)
	{
		// if (((t_parsed_word *)current->content)->type == W_PLAIN)
		// 	add_back_new_list(current->content, &expanding_tokens, no_del);
		// else if (((t_parsed_word *)current->content)->type == W_SINGLE_QUOTED)
		// 	add_back_new_list(current->content, &expanding_tokens, no_del);
		// else if (((t_parsed_word *)current->content)->type == W_DOUBLE_QUOTED)
		// {
		// 	expanded_str = expand_heredoc(((t_parsed_word *)current->content)->str,
		// 			env);
		// 	if (expanded_str == NULL)
		// 		return (NULL);
		// 	add_back_new_list(expanded_str, &expanding_tokens, free);
		// }
		current = current->next;
	}
	return (expanding_tokens);
}
