/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:01:43 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 03:20:32 by katakada         ###   ########.fr       */
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
t_list				*split_operator_word(char **parsed_word_str);
t_list				*expand_plain_word(t_list *current_words, t_env env);

// expand__env_var__expand_quoted_word.c
t_list				*expand_single_quoted_word(char *str);
t_list				*expand_double_quoted_word(char *to_expand, t_env env);

// expand__env_var__split__utils.c
void				delete_prefix_separator(t_list **ex_tokens);
void				to_next_separate_top(t_list **current_token);
t_list				*split_unquoted_word(char **to_expand);

// expand__env_var__split_post_expanded__utils.c
t_binary_result		split_unquoted_str_before_1st_separator(t_list *current_token);

// expand__env_var__split_post_expanded.c
void				delete_prefix_separator(t_list **ex_tokens);
t_binary_result		split_post_expanded_unquoted_str(t_list **ex_tokens);

// expand__env_var__utils.c
t_list				*init_expanding_token(t_e_token_type type);
t_bool				is_valid_env_cahr(char env_char);
t_bool				is_death_dollar(char *parsed_word_str);
t_bool				is_delimiter_for_unquoted(char *word);
t_bool				can_use_raw_cahr(char c);

// expand__env_var.c
char				*expand_dollar(char **dollar_str, t_env env);
char				*use_raw_str_when_double_quoted(char **raw_str);
t_list				*expand_env_var_with_expanding_tokens(t_list *parsed_words,
						t_env env);

// expand__wildcard.c
t_binary_result		expand_wildcard(t_list **expanding_tokens);

// expand_abs_node.c
t_binary_result		expand_abs_node(t_abs_node *abs_node, t_env env);

// expander__utils.c
t_expanding_token	*get_ex_token(t_list **expanding_tokens);
void				free_expanding_token(void *content);
char				**expanding_tokens_to_arg_list(t_list *expanding_tokens);

#endif
