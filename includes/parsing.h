#ifndef PARSING_H
# define PARSING_H

# include "../libraries/libft.h"
# include "minishell.h"

# define OK 1
# define NG 0

typedef enum e_loop_status
{
	STOP = 0,
	CONTINUE = 1,
}				t_loop_status;

// grammar dictionary
# define REDIRECT_OP " << >> < >"
# define SUBSHELL_OP " ( )"
# define BINARY_OP_PIPE " && || |"
# define G_OPERATORS " && || | ' \""

// typedef struct s_abs_node	t_abs_node;
// typedef enum e_abs_node_type
// {
// 	BINARY_OP,
// 	HEREDOC,
// 	REDIRECT,
// 	COMMAND
// }							t_abs_node_type;

// struct						s_abs_node
// {
// 	t_abs_node_type			node_type;
// 	t_token					*token; // token->typeで演算子を識別できます
// 	t_list						*cmd_args; // 対象となるコマンドブロックのtoken_listを持ちます
// 	char					**expanded_args;
// node_typeがHEREDOCの場合、０番目にファイルディスクリプター番号がstringを入れておいて、パイプライン処理の時にその番号を使う
// 	t_abs_node				*left;
// 	t_abs_node				*right;
// };

typedef int		(*t_gram_shell_term)(t_list **, int *);
typedef int		(*t_gram_operator)(t_list **, int);
typedef int		(*t_gram_redirect)(t_list **, int, t_bool *);

// check_grammar.c
int				check_tokens_grammar(t_list **token_list, int *subshell_depth);

// grammar__follower.c
int				grammar_next_token(t_token *test_token, t_list **next_tokens,
					int *subshell_depth, t_bool *strict_mode);

// grammar__prefix.c
int				grammar_prefix(t_token *test_token, int subshell_depth);

// grammar__utils.c
t_list			**forward_token_list(t_list **current_token_list);
t_token			*get_token(t_list *current_token);
t_bool			is_in(char *dict, t_token *test_token);
t_bool			is_operand_text(t_token *test_token);
int				gf(t_token *testing_token, char *dict);

// grammar_binop_pipe.c
int				grammar_binop_and(t_list **next_tokens, int subshell_depth);
int				grammar_binop_or(t_list **next_tokens, int subshell_depth);
int				grammar_pipe(t_list **next_tokens, int subshell_depth);

// grammar_quote.c
int				grammar_quote_single(t_list **next_tokens, int subshell_depth);
int				grammar_quote_double(t_list **next_tokens, int subshell_depth);
t_bool			is_correct_quoting(t_list *next_to_quote_tokens,
					t_token_type quote_token_type);

// grammar_redirect.c
int				grammar_heredoc(t_list **next_tokens, int subshell_depth,
					t_bool *strict_mode);
int				grammar_re_append(t_list **next_tokens, int subshell_depth,
					t_bool *strict_mode);
int				grammar_re_input(t_list **next_tokens, int subshell_depth,
					t_bool *strict_mode);
int				grammar_re_output(t_list **next_tokens, int subshell_depth,
					t_bool *strict_mode);

// grammar_subshell_to_redirect.c
int				grammar_subshell_to_redirect(t_list **next_tokens,
					t_bool *strict_mode);

// grammar_subshell.c
int				grammar_sub_open(t_list **next_tokens, int *subshell_depth);
int				grammar_sub_close(t_list **next_tokens, int *subshell_depth);
int				grammar_terminator(t_list **next_tokens, int *subshell_depth);

// grammar_text.c

int				grammar_operand_text(t_token *test_token, t_list **next_tokens,
					int subshell_depth, t_bool *strict_mode);

// parse.c
t_exit_status	parse(t_list *token_list, t_list **abs_tree);
void			free_abs_node(void *target);

// put_syntax_err.c
void			put_syntax_err(t_list *token_list);

#endif