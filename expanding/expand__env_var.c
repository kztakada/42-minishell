/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand__env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:06:51 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 05:02:42 by katakada         ###   ########.fr       */
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

t_list	*expand_operator_word(char **parsed_word_str)
{
	t_list	*under_expanding_token;

	if (parsed_word_str == NULL || *parsed_word_str == NULL)
		return (NULL);
	under_expanding_token = NULL;
	if (**parsed_word_str == '*')
	{
		under_expanding_token = init_expanding_token(ET_WILDCARD);
		(*parsed_word_str)++;
	}
	else if (is_ifs(**parsed_word_str))
	{
		under_expanding_token = init_expanding_token(ET_SEPARATOR);
		while (is_ifs(**parsed_word_str))
			(*parsed_word_str)++;
	}
	if (under_expanding_token == NULL)
		return (NULL);
	return (under_expanding_token);
}

t_list	*expand_death_dollar_word(char **parsed_word_str)
{
	t_list	*under_expanding_token;

	under_expanding_token = init_expanding_token(ET_DEATH_DOLLAR);
	(*parsed_word_str)++;
	if (under_expanding_token == NULL)
		return (NULL);
	return (under_expanding_token);
}

t_bool	is_valid_env_cahr(char env_char)
{
	if (ft_isalnum(env_char) || env_char == '_')
		return (TRUE);
	return (FALSE);
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

char	*expand_normal_str(char **normal_str)
{
	char	*normal_str_value;
	int		i;

	i = 0;
	while ((*normal_str)[i] != '\0' && (*normal_str)[i] != '$'
		&& (*normal_str)[i] != '*' && !is_ifs((*normal_str)[i]))
		i++;
	normal_str_value = ft_substr(*normal_str, 0, i);
	if (normal_str_value == NULL)
		return (NULL);
	*normal_str = *normal_str + i;
	return (normal_str_value);
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

char	*expand_double_quoted_str(char **normal_str)
{
	char	*normal_str_value;
	int		i;

	i = 0;
	while ((*normal_str)[i] != '\0' && (*normal_str)[i] != '$')
		i++;
	normal_str_value = ft_substr(*normal_str, 0, i);
	if (normal_str_value == NULL)
		return (NULL);
	*normal_str = *normal_str + i;
	return (normal_str_value);
}

t_list	*expand_double_quoted_word(char *to_expand, t_env env)
{
	char				*d_quoted_str;
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	d_quoted_str = strdup("");
	if (d_quoted_str == NULL)
		return (NULL);
	while (*to_expand != '\0')
	{
		if (*to_expand == '$')
			d_quoted_str = strjoin_free(d_quoted_str, expand_dollar(&to_expand,
						env));
		else
			d_quoted_str = strjoin_free(d_quoted_str,
					expand_double_quoted_str(&to_expand));
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

t_list	*expand_unquoted_word(char **to_expand, t_env env)
{
	char				*unquoted_str;
	t_list				*expanded_token;
	t_expanding_token	*expanding_token;

	unquoted_str = strdup("");
	if (unquoted_str == NULL)
		return (NULL);
	while (!is_ifs(**to_expand) && **to_expand != '\0' && **to_expand != '*'
		&& !is_death_dollar(*to_expand))
	{
		if (**to_expand == '$')
			unquoted_str = strjoin_free(unquoted_str, expand_dollar(to_expand,
						env));
		else
			unquoted_str = strjoin_free(unquoted_str,
					expand_normal_str(to_expand));
		if (unquoted_str == NULL)
			return (ft_lstclear(&expanded_token, free_expanding_token), NULL);
	}
	expanded_token = init_expanding_token(ET_UNQUOTED_STR);
	if (expanded_token == NULL)
		return (free(unquoted_str), ft_lstclear(&expanded_token,
				free_expanding_token), NULL);
	expanding_token = (t_expanding_token *)expanded_token->content;
	expanding_token->str = unquoted_str;
	return (expanded_token);
}

t_list	*expand_plain_word(t_list *current_words, t_env env)
{
	t_list	*expanded_tokens;
	t_list	*under_expanding_token;
	char	*parsed_word_str;

	parsed_word_str = ((t_parsed_word *)current_words->content)->str;
	if (parsed_word_str == NULL)
		return (NULL);
	expanded_tokens = NULL;
	while (*parsed_word_str != '\0')
	{
		if (*parsed_word_str == '*' || is_ifs(*parsed_word_str))
			under_expanding_token = expand_operator_word(&parsed_word_str);
		else if (is_death_dollar(parsed_word_str))
			under_expanding_token = expand_death_dollar_word(&parsed_word_str);
		else
			under_expanding_token = expand_unquoted_word(&parsed_word_str, env);
		if (under_expanding_token == NULL)
			return (ft_lstclear(&expanded_tokens, free_expanding_token), NULL);
		ft_lstadd_back(&expanded_tokens, under_expanding_token);
	}
	return (expanded_tokens);
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
	return (expanded_tokens);
}
