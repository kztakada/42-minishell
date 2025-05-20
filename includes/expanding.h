/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:01:43 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 17:06:17 by katakada         ###   ########.fr       */
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
// ET_DEATH_DOLLAR is when there is a dollar sign at the end of
// the argument clause.  In this case, after the environment variable
// is expanded, the ifs delimiter in the clause is completely ignored,
// even though it is not quoted, a very very crazy case!
typedef enum e_expanding_token_type
{
	ET_WILDCARD,
	ET_SEPARATOR,
	ET_UNQUOTED_STR,
	ET_QUOTED_STR,
	ET_DEATH_DOLLAR,
}					t_e_token_type;
typedef struct s_expanding_word
{
	t_e_token_type	type;
	char			*str;
}					t_expanding_token;

// ambiguous_redirection.c
t_bool				is_ambiguous_redirection(t_list *expanding_tokens);
void				put_ambiguous_redirection_err(t_list *file_name_words);

// expand__env_var__expand_plain_word.c
t_list				*expand_plain_word(t_list *current_words, t_env env);

// expand__env_var__expand_quoted_word.c
t_list				*expand_single_quoted_word(char *str);
t_list				*expand_double_quoted_word(char *to_expand, t_env env);

// expand__env_var__utils.c
t_list				*init_expanding_token(t_e_token_type type);
t_bool				is_valid_env_cahr(char env_char);
t_bool				is_death_dollar(char *parsed_word_str);

// expand__env_var.c
char				*get_envlst_val(char *name, t_list *envlst);
char				*expand_dollar(char **dollar_str, t_env env);
char				*expand_normal_str(char **normal_str);
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
