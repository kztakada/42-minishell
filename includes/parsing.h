#ifndef PARSING_H
# define PARSING_H

# include "../libraries/libft.h"
# include "minishell.h"

# define OK 1
# define NG 0

// grammar dictionary
# define NO_USE_FIRST " && || | )"
# define REDIRECT_OP " << >> < >"
# define SUBSHELL_OP " ( )"
# define BINARY_OP_PIPE " && || |"

// check_following_others.c
int		check_following_binop_and(t_token *testing_token);
int		check_following_binop_or(t_token *testing_token);
int		check_following_pipe(t_token *testing_token);

// check_following_redirect.c
int		check_following_re_heredoc(t_token *testing_token);
int		check_following_re_append(t_token *testing_token);
int		check_following_re_input(t_token *testing_token);
int		check_following_re_output(t_token *testing_token);

// check_following_subshell.c
int		check_following_sub_open(t_token *testing_token);
int		check_following_sub_close(t_token *testing_token);

// check_following_text.c
int		check_following_quote_single(t_token *testing_token);
int		check_following_quote_double(t_token *testing_token);
int		check_following_operand_text(t_token *testing_token);
int		check_following_terminator(t_token *testing_token);

// check_following.c
int		check_following_redirect(t_token *testing_token);
int		check_following_subshell(t_token *testing_token);
int		check_following_binop_pipe(t_token *testing_token);
int		check_following_text(t_token *testing_token);

// check_grammar__utils.c
void	forward_token_list(t_list **current_token_list);
t_token	*get_token(t_list *current_token);

// check_grammar.c
int		check_tokens_grammar(t_list *token_list);

// grammar.c
t_bool	can_use_as_first_token(t_token *token);

// parse.c
int		parse(t_list *token_list, t_list **abs_tree);
void	free_abs_node(void *target);

#endif