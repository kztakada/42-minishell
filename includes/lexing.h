#ifndef LEXING_H
# define LEXING_H

# include "../libraries/libft.h"

typedef enum e_token_type
{
	OP_HEREDOC,   // <<
	OP_APPEND,    // >>
	OP_AND,       // &&
	OP_OR,        // ||
	OP_PIPE,      // |
	OP_INPUT,     // <
	OP_OUTPUT,    // >
	OP_OPEN,      // (
	OP_CLOSE,     // )
	QUOTE_SINGLE, // '
	QUOTE_DOUBLE, // "
	TERMINATOR,   // \n
	OPERAND_TEXT, // identifier
}						t_token_type;

typedef struct s_token	t_token;
struct					s_token
{
	t_token_type		type;
	char				*content;
};

// lexer.c
int						lexer(char *input, t_list **token_list);

// lexicize_func_sign.c
int						add_token_to_list(t_token *token, t_list **token_list);
int						lexicize_func_sign(char *input, t_list **token_list);
int						append_terminator(t_list **token_list);

// lexicize_text.c
int						lexicize_operand(char *input, t_list **token_list);
int						lexicize_text_in_quote(char *input, t_list **token_list,
							char quote);

// lexing_utils.c
int						is_ifs(char c);
int						is_quote(char c);
int						is_operator(char *str);
void					free_token(void *target);

#endif