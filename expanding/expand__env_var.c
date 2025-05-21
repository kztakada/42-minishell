/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:06:51 by katakada          #+#    #+#             */
/*   Updated: 2025/05/21 16:03:00 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"

static char	*get_envlst_val(char *name, t_list *envlst)
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

char	*expand_dollar(char **dollar_str, t_env env)
{
	char	*env_name;
	char	*env_value;
	int		i;

	*dollar_str = *dollar_str + 1;
	i = 0;
	if ((*dollar_str)[i] == '?')
	{
		*dollar_str = *dollar_str + 1;
		return (ft_itoa(*(env.exit_status)));
	}
	else if (is_valid_env_cahr((*dollar_str)[i]) == FALSE)
		return (ft_strdup("$"));
	while (is_valid_env_cahr((*dollar_str)[i]))
		i++;
	env_name = ft_substr((*dollar_str), 0, i);
	if (env_name == NULL)
		return (NULL);
	*dollar_str = *dollar_str + i;
	env_value = get_envlst_val(env_name, env.env_vars);
	if (!env_value)
		return (free(env_name), ft_strdup(""));
	return (free(env_name), ft_strdup(env_value));
}

char	*use_raw_str_when_double_quoted(char **raw_str)
{
	char	*raw_str_value;
	int		i;

	i = 0;
	while ((*raw_str)[i] != '\0' && (*raw_str)[i] != '$')
		i++;
	raw_str_value = ft_substr(*raw_str, 0, i);
	if (raw_str_value == NULL)
		return (NULL);
	*raw_str = *raw_str + i;
	return (raw_str_value);
}

t_list	*expand_env_var_with_expanding_tokens(t_list *parsed_words, t_env env)
{
	t_list			*under_expanding_token;
	t_list			*expanded_tokens;
	t_list			*current_words;
	t_parsed_word	*parsed_word;

	current_words = parsed_words;
	expanded_tokens = NULL;
	while (current_words != NULL)
	{
		parsed_word = (t_parsed_word *)current_words->content;
		if (parsed_word->type == W_SINGLE_QUOTED)
			under_expanding_token = expand_single_quoted_word(parsed_word->str);
		else if (parsed_word->type == W_DOUBLE_QUOTED)
			under_expanding_token = expand_double_quoted_word(parsed_word->str,
					env);
		else
			under_expanding_token = expand_plain_word(current_words, env);
		if (under_expanding_token == NULL)
			return (ft_lstclear(&expanded_tokens, free_expanding_token), NULL);
		ft_lstadd_back(&expanded_tokens, under_expanding_token);
		forward_token_list(&current_words);
	}
	if (split_post_expanded_unquoted_str(&expanded_tokens) == FAILURE_BIN_R)
		return (ft_lstclear(&expanded_tokens, free_expanding_token), NULL);
	return (expanded_tokens);
}
