#ifndef PARSING_H
# define PARSING_H

# include "../libraries/libft.h"
# include "minishell.h"

// grammar dictionary
# define REDIRECT_OP " << >> < >"
# define SUBSHELL_OP " ( )"
# define BIN_OP " && ||"
# define G_OPERATORS " && || | ' \""

// grammar dictionary for phrasing
# define CMD_MEMBER_OP " << >> < > ' \""
# define NOT_CMD_MEMBER_OP " && || | ( ) \n"

typedef enum e_binary_result
{
	FAILURE_BIN_R = -1,
	SUCCESS_BIN_R = 0,
}							t_binary_result;

typedef enum e_grammar
{
	NG_G = 0,
	OK_G = 1,
}							t_grammar;

typedef enum e_parsing
{
	FAILURE_P = -1,
	SYNTAX_ERROR_P = 0,
	SUCCESS_P = 1,

}							t_parsing;

typedef enum e_loop_status
{
	MEMORY_ERR = -1,
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
	char					*str;
}							t_parsed_text;
// t_redirection ***********************************************
typedef enum e_redirect_op_type
{
	RE_OP_HEREDOC,
	RE_OP_APPEND,
	RE_OP_INPUT,
	RE_OP_OUTPUT,
}							t_redirect_op_type;
// filename is t_parsed_text list
// if heredoc, filename is EOF
typedef struct s_redirection
{
	t_redirect_op_type		type;
	int						fd;
	t_list					*file_name;
	char					*expanded_file_name;
}							t_redirection;
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
// redirection_list is list of t_redirection
struct						s_abs_node
{
	t_abs_node_type			type;
	t_list					*command_args;
	char					**expanded_args;
	t_list					*redirection_list;
	t_abs_node				*left;
	t_abs_node				*right;
};
// for parse_token handling *************************************
typedef enum s_node_pos
{
	LEFT,
	B_OP_RIGHT,
	PIPE_RIGHT,
}							t_node_pos;
// heredoc_list is list of t_redirection of heredoc only
typedef struct s_parse_log
{
	int						subshell_depth;
	t_abs_node				*tree_top_node;
	t_abs_node				*working_node;
	t_node_pos				working_node_pos;
	t_list					*heredoc_list;
}							t_parsing_state;
//**************************************************************/
typedef int					(*t_gram_shell_term)(t_list **, int *);
typedef int					(*t_gram_operator)(t_list **, int);
typedef int					(*t_gram_redirect)(t_list **, int, t_bool *);

// check_grammar.c
int							check_tokens_phrase_grammar(t_list **current_tokens,
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
t_bool						has_ifs(char *str);

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

// parser_utils.c
void						free_abs_tree(t_abs_node *abs_tree);
void						no_del(void *target);

// parser.c
t_exit_status				parser(t_list *input_tokens, t_abs_node **abs_tree);
t_parsing					parse_subshell_input(t_list **input_tokens,
								t_abs_node **abs_tree,
								t_parsing_state *parse_log);

// put_syntax_err.c
void						put_syntax_err(t_list *token_list);

// treeing__add_content_to_working_abs_node.c
t_binary_result				add_content_to_working_abs_node(t_list *tokens_begin,
								t_list *tokens_end,
								t_parsing_state *parsing_state);

// treeing__append_to_parsed_texts.c
t_binary_result				append_quoted_to_parsed_texts(t_list **current_tokens,
								t_list **parsed_texts);
t_binary_result				append_plain_text_to_parsed_texts(t_list **current_tokens,
								t_list **parsed_texts);
t_binary_result				append_only1st_text_to_parsed_texts(t_list **current_tokens,
								t_list **parsed_texts);
t_binary_result				append_chaintexts_to_file_name(t_list **current_tokens,
								t_token *end_token, t_list **file_name);

// treeing__convert_into_abs_tree.c
t_binary_result				convert_into_abs_tree(t_list *tokens_begin,
								t_list *tokens_end, t_abs_node **abs_tree,
								t_parsing_state *parsing_state);
t_abs_node					*init_abs_node(t_parsing_state *parsing_state);

// treeing__utils.c
t_binary_result				add_back_new_list(void *content,
								t_list **existing_list, void (*del)(void *));
void						free_parsed_text(void *content);
void						free_redirection(void *content);

#endif