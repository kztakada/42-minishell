#ifndef LEXING_H
# define LEXING_H

# include "minishell.h"

// lexicize_func_sign.c
int	add_token_to_list(t_token *token, t_list **token_list);
int	lexicize_func_sign(char *input, t_list **token_list);
int	append_terminator(t_list **token_list);

// lexicize_text.c
int	lexicize_text(char *input, t_list **token_list);
int	lexicize_text_in_quote(char *input, t_list **token_list, char quote);

// lexing_utils.c
int	is_quote(char c);
int	is_operator(char *str);

#endif