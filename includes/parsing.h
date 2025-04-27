#ifndef PARSING_H
# define PARSING_H

# include "../libraries/libft.h"
# include "minishell.h"

# define OK 1
# define NG 0

// grammar dictionary
# define NO_USE_FIRST " && || |"
# define REDIRECT_OP " << >> < >"
# define SUBSHELL_OP " ( )"
# define SUBSHELL_TERM " ( ) \n"
# define BINARY_OP_PIPE " && || |"

// check_following_others.c
int		check_following_binop_and(t_list **follower_list);
int		check_following_binop_or(t_list **follower_list);
int		check_following_pipe(t_list **follower_list);

// check_following_redirect.c
int		check_following_re_heredoc(t_list **follower_list);
int		check_following_re_append(t_list **follower_list);
int		check_following_re_input(t_list **follower_list);
int		check_following_re_output(t_list **follower_list);

// check_following_subshell.c
int		check_following_sub_open(t_list **follower_list, int *subshell_count);
int		check_following_sub_close(t_list **follower_list, int *subshell_count);
int		check_following_terminator(t_list **follower_list, int *subshell_count);

// check_following_text.c
int		check_following_quote_single(t_list **follower_list);
int		check_following_quote_double(t_list **follower_list);
int		check_following_operand_text(t_token *testing_token,
			t_list **follower_list);

// check_following.c
int		check_following_redirect(t_token *testing_token,
			t_list **follower_list);
int		check_following_subshell(t_token *testing_token, t_list **follower_list,
			int *subshell_count);
int		check_following_binop_pipe(t_token *testing_token,
			t_list **follower_list);
int		check_following_text(t_token *testing_token, t_list **follower_list);

// check_grammar__utils.c
void	forward_token_list(t_list **current_token_list);
t_token	*get_token(t_list *current_token);
t_bool	is_in(t_token *testing_token, char *dict);

// check_grammar.c
int		check_tokens_grammar(t_list **token_list, int *subshell_count);

// grammar.c
t_bool	can_use_as_first_token(t_token *token);

// parse.c
int		parse(t_list *token_list, t_list **abs_tree);
void	free_abs_node(void *target);

#endif