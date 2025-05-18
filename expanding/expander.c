/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:57:12 by katakada          #+#    #+#             */
/*   Updated: 2025/05/14 19:43:17 by katakada         ###   ########.fr       */
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

// static char	*expand_env_var(char **input, t_env env)
// {
// 	char	*var_name;
// 	char	*var_value;
// 	int		i;

// 	if (*input == NULL)
// 		return (NULL);
// 	if (**input == '?')
// 	{
// 		var_value = ft_itoa((int)(*env.exit_status));
// 		if (var_value == NULL)
// 			return (perror(ERROR_MALLOC), NULL);
// 		(*input)++;
// 		return (var_value);
// 	}
// 	var_name = ft_strdup(*input);
// 	if (var_name == NULL)
// 		return (perror(ERROR_MALLOC), NULL);
// 	i = 0;
// 	while (var_name[i] != '\0' && !is_ifs(var_name[i]))
// 		i++;
// 	*input = *input + i;
// 	if (is_ifs(var_name[i]))
// 		var_name[i] = '\0';
// 	var_value = get_envlst_val(var_name, env.env_lists);
// 	return (free(var_name), var_value);
// }

// char	*strjoin_free(char *s1, char *s2)
// {
// 	char	*result;
// 	t_bool	can_free_s1;
// 	t_bool	can_free_s2;

// 	can_free_s1 = TRUE;
// 	can_free_s2 = TRUE;
// 	if (s1 == NULL)
// 	{
// 		s1 = "";
// 		can_free_s1 = FALSE;
// 	}
// 	if (s2 == NULL)
// 	{
// 		s2 = "";
// 		can_free_s2 = FALSE;
// 	}
// 	result = ft_strjoin(s1, s2);
// 	if (result == NULL)
// 		return (perror(ERROR_MALLOC), NULL);
// 	if (can_free_s1 == TRUE)
// 		free(s1);
// 	if (can_free_s2 == TRUE)
// 		free(s2);
// 	return (result);
// }

// char	*e_handle_substr(char *to_expand, int len)
// {
// 	char	*tmp;

// 	tmp = ft_substr(to_expand, 0, len);
// 	if (tmp == NULL)
// 		return (perror(ERROR_MALLOC), NULL);
// 	return (tmp);
// }

// static char	*expand_text(char *to_expand, t_env env)
// {
// 	char	*origin;
// 	char	*expanded;
// 	int		plain_str_len;

// 	origin = to_expand;
// 	expanded = NULL;
// 	while (*to_expand != '\0')
// 	{
// 		if (*to_expand == '$')
// 		{
// 			to_expand++;
// 			expanded = e_handle_strjoin_free(expanded,
// 					expand_env_var(&to_expand, env));
// 		}
// 		else
// 		{
// 			plain_str_len = 0;
// 			while (to_expand[plain_str_len] != '\0'
// 				&& to_expand[plain_str_len] != '$')
// 				plain_str_len++;
// 			expanded = strjoin_free(expanded, e_handle_substr(to_expand,
// 						plain_str_len));
// 			to_expand = to_expand + plain_str_len;
// 		}
// 	}
// 	free(origin);
// 	return (expanded);
// }

// t_exit_status	expander(t_abs_node *abs_tree, t_env env)
// {
// 	return (EXIT_S_SUCCESS);
// }
