#ifndef PARSING_H
# define PARSING_H

# include "../libraries/libft.h"
# include "minishell.h"

// grammar dictionary
# define REDIRECT_OP " << >> < >"
# define SUBSHELL_OP " ( )"
# define BINARY_OP_PIPE " && || |"
# define G_OPERATORS " && || | ' \""

typedef enum e_grammar
{
	OK_G = 1,
	NG_G = 0,
}							t_grammar;

typedef enum e_loop_status
{
	STOP = 0,
	CONTINUE = 1,
}							t_loop_status;

// t_parsed_text **********************************************
typedef enum e_parsed_text_type
{
	PLAIN_TEXT,
	DOUBLE_QUOTED,
	SINGLE_QUOTED,
}							t_parsed_text_type;
typedef struct s_parsed_text
{
	t_parsed_text_type		type;
	char					*text;
}							t_parsed_text;
// t_redirect ***********************************************
typedef enum e_redirect_op_type
{
	RE_OP_HEREDOC,
	RE_OP_APPEND,
	RE_OP_INPUT,
	RE_OP_OUTPUT,
}							t_redirect_op_type;
// filename is t_parsed_text list
typedef struct s_redirect
{
	t_redirect_op_type		type;
	int						fd;
	t_list					*file_name;
	char					*expanded_file_name;
}							t_redirect;
// abs_node ****************************************************
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	BINOP_AND,
	BINOP_OR,
	PIPE,
	COMMAND
}							t_abs_node_type;
// command_args is list of t_parsed_text
// redirect_list is list of t_redirect
struct						s_abs_node
{
	t_abs_node_type			type;
	t_list					*command_args;
	char					**expanded_args;
	t_list					*redirect_list;
	t_abs_node				*left;
	t_abs_node				*right;
};
// for parse_token handling *************************************
typedef enum s_parse_status
{
	LEFT,
	B_OP_RIGHT,
	PIPE_RIGHT,
}							t_parse_status;
// heredoc_list is list of t_redirect of heredoc only
typedef struct s_parse_log
{
	int						subshell_depth;
	t_parse_status			status;
	t_list					*heredoc_list;
}							t_parse_log;
//**************************************************************/
typedef int					(*t_gram_shell_term)(t_list **, int *);
typedef int					(*t_gram_operator)(t_list **, int);
typedef int					(*t_gram_redirect)(t_list **, int, t_bool *);

// check_grammar.c
int							check_tokens_grammar(t_list **token_list,
								int *subshell_depth);

// grammar__follower.c
int							grammar_next_token(t_token *test_token,
								t_list **next_tokens, int *subshell_depth,
								t_bool *strict_mode);

// grammar__prefix.c
int							grammar_prefix(t_token *test_token,
								int subshell_depth);

// grammar__utils.c
t_list						**forward_token_list(t_list **current_token_list);
t_token						*get_token(t_list *current_token);
t_bool						is_in(char *dict, t_token *test_token);
t_bool						is_operand_text(t_token *test_token);
int							gf(t_token *testing_token, char *dict);

// grammar_binop_pipe.c
int							grammar_binop_and(t_list **next_tokens,
								int subshell_depth);
int							grammar_binop_or(t_list **next_tokens,
								int subshell_depth);
int							grammar_pipe(t_list **next_tokens,
								int subshell_depth);

// grammar_quote.c
int							grammar_quote_single(t_list **next_tokens,
								int subshell_depth);
int							grammar_quote_double(t_list **next_tokens,
								int subshell_depth);
t_bool						is_correct_quoting(t_list *next_to_quote_tokens,
								t_token_type quote_token_type);

// grammar_redirect.c
int							grammar_heredoc(t_list **next_tokens,
								int subshell_depth, t_bool *strict_mode);
int							grammar_re_append(t_list **next_tokens,
								int subshell_depth, t_bool *strict_mode);
int							grammar_re_input(t_list **next_tokens,
								int subshell_depth, t_bool *strict_mode);
int							grammar_re_output(t_list **next_tokens,
								int subshell_depth, t_bool *strict_mode);

// grammar_subshell_to_redirect.c
int							grammar_subshell_to_redirect(t_list **next_tokens,
								t_bool *strict_mode);

// grammar_subshell.c
int							grammar_sub_open(t_list **next_tokens,
								int *subshell_depth);
int							grammar_sub_close(t_list **next_tokens,
								int *subshell_depth);
int							grammar_terminator(t_list **next_tokens,
								int *subshell_depth);

// grammar_text.c

int							grammar_operand_text(t_token *test_token,
								t_list **next_tokens, int subshell_depth,
								t_bool *strict_mode);

// parse_heredoc.c
t_exit_status				parse_heredoc(t_list *input_tokens,
								t_list *next_tokens, t_abs_node **abs_tree,
								t_parse_log *perse_log);
void						call_heredoc(t_parse_log *perse_log);

// parse_token.c
t_exit_status				parse_token(t_list *input_tokens,
								t_list *next_tokens, t_abs_node **abs_tree,
								t_parse_log *perse_log);

// parser_utils.c
void						free_abs_tree(t_abs_node *abs_tree);
void						no_del(void *target);

// parser.c
t_exit_status				parser(t_list *input_tokens, t_abs_node **abs_tree);
t_exit_status				parse_subshell_input(t_list **input_tokens,
								t_abs_node **abs_tree, t_parse_log *parse_log);

// put_syntax_err.c
void						put_syntax_err(t_list *token_list);

#endif