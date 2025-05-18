/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:01:43 by katakada          #+#    #+#             */
/*   Updated: 2025/05/18 20:53:08 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

# include "t_minishell.h"

// typedef enum e_expanding
// {
// 	FAILURE_EX = -1,
// 	AMBIGUOUS_R_ERROR_EX = 0,
// 	SUCCESS_EX = 1,

// }						t_expanding;
// t_expanded_word **********************************************
typedef enum e_expanding_token_type
{
	ET_WILDCARD,
	ET_SEPARATOR,
	ET_EXPANDED_STR,
}					t_e_token_type;
typedef struct s_expanding_word
{
	t_e_token_type	type;
	char			*str;
}					t_expanding_token;

// ambiguous_redirection.c
t_bool				is_ambiguous_redirection(t_list *expanding_tokens);
void				put_ambiguous_redirection_err(t_list *file_name_words);

// expand__env_var.c
char				*get_envlst_val(char *name, t_list *envlst);
t_list				*expand_env_var_with_expanding_tokens(t_list *parsed_words,
						t_env env);

// expand__wildcard.c
t_binary_result		expand_wildcard(t_list **expanding_tokens);

// expand_abs_node.c
t_binary_result		expand_abs_node(t_abs_node *abs_node, t_env env);

// expander__utils.c
void				free_expanding_token(void *content);
char				**expanding_tokens_to_str_list(t_list *expanding_tokens);

#endif
