/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_minishell.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:41:25 by katakada          #+#    #+#             */
/*   Updated: 2025/05/20 18:19:04 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_MINISHELL_H
# define T_MINISHELL_H

# include "minishell.h"

# define PROMPT "minishell$ "
# define HEREDOC_PROMPT "> "

# define FAILURE -1
# define SUCCESS 0

// t_parsed_word **********************************************
typedef enum e_parsed_word_type
{
	W_PLAIN,
	W_DOUBLE_QUOTED,
	W_SINGLE_QUOTED,
}							t_parsed_word_type;
typedef struct s_parsed_word
{
	t_parsed_word_type		type;
	char					*str;
}							t_parsed_word;
// t_redirection ***********************************************
typedef enum e_redirect_op_type
{
	RE_OP_HEREDOC,
	RE_OP_APPEND,
	RE_OP_INPUT,
	RE_OP_OUTPUT,
}							t_redirect_op_type;
// filename is t_parsed_word list
// if heredoc, filename is EOF
typedef struct s_redirection
{
	t_redirect_op_type		type;
	int						fd;
	t_list					*file_name_words;
	char					*expanded_file_name;
}							t_redirection;
// abs_node ****************************************************
typedef struct s_abs_node	t_abs_node;
typedef enum e_abs_node_type
{
	ABS_BIN_AND,
	ABS_BIN_OR,
	ABS_PIPE,
	ABS_COMMAND
}							t_abs_node_type;
// cmd_words is list of t_parsed_word
// redirections is list of t_redirection
struct						s_abs_node
{
	t_bool					is_subshell;
	t_abs_node_type			type;
	t_list					*cmd_words;
	char					**expanded_args;
	t_list					*redirections;
	t_abs_node				*left;
	t_abs_node				*right;
};
//**************************************************************/
// init_env__utils.c
void						free_env_var(void *env_var);

// init_env.c
t_list						*init_envlst(char **env);

// lexer.c
t_exit_status				lexer(char *input, t_list **token_list);

// parser.c
t_exit_status				parser(t_list *input_tokens, t_abs_node **abs_tree,
								t_env env);

// expander.c
t_exit_status				expander(t_abs_node *abs_tree, t_env env);

// parser_utils.c
void						free_abs_tree(t_abs_node *abs_tree);

#endif
