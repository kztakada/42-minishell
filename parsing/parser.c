/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 17:57:01 by katakada          #+#    #+#             */
/*   Updated: 2025/05/16 11:53:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

// static void	print_file_name(t_list *file_name) //テスト用
// {
// 	t_parsed_text *parsed_text;

// 	while (file_name != NULL)
// 	{
// 		parsed_text = (t_parsed_text *)file_name->content;
// 		printf("		file name type: %d\n", parsed_text->type);
// 		printf("		file name: %s\n", parsed_text->str);
// 		file_name = file_name->next;
// 	}
// }

// static void	print_heredoc_list(t_list *heredoc_list) //テスト用
// {
// 	t_redirection *redirection;

// 	while (heredoc_list != NULL)
// 	{
// 		redirection = (t_redirection *)heredoc_list->content;
// 		printf("heredoc type: %d\n", redirection->type);
// 		print_file_name(redirection->file_name);
// 		heredoc_list = heredoc_list->next;
// 	}
// }

// one sequence means one of the following
// one subshell block | one command node | one binary node | one pipe node
t_parsing	parse_one_sequence(t_list *input_tokens, t_list **sequence_end,
		t_abs_node **abs_tree, t_parsing_state *parsing_state)
{
	t_grammar		g_result;
	t_binary_result	treeing_result;
	t_list			*phrasing_tokens;

	if (input_tokens == NULL)
		return (FAILURE_P);
	phrasing_tokens = input_tokens;
	g_result = check_one_phrase_grammar(&phrasing_tokens,
			&(parsing_state->subshell_depth));
	if (g_result == NG_G)
	{
		put_syntax_err(phrasing_tokens);
		parsing_state->subshell_depth = 0;
		return (SYNTAX_ERROR_P);
	}
	*sequence_end = phrasing_tokens;
	if (is_in(SUBSHELL_OP, get_token(input_tokens)))
		return (subshell_tokens_to_abs_tree(input_tokens, sequence_end,
				abs_tree, parsing_state));
	treeing_result = tokens_to_abs_tree(input_tokens, *sequence_end, abs_tree,
			parsing_state);
	if (treeing_result == SUCCESS_BIN_R)
		return (SUCCESS_P);
	else
		return (FAILURE_P);
}

static t_parsing	parse_input(t_list *input_tokens, t_abs_node **abs_tree,
		t_parsing_state *parsing_state, t_env env)
{
	t_list		*sequence_end;
	t_parsing	p_result;

	p_result = SUCCESS_P;
	sequence_end = NULL;
	while (get_token(input_tokens)->type != TERMINATOR && p_result == SUCCESS_P)
	{
		p_result = parse_one_sequence(input_tokens, &sequence_end, abs_tree,
				parsing_state);
		if (p_result == FAILURE_P)
			break ;
		if (parsing_state->heredoc_list != NULL
			&& parsing_state->subshell_depth == 0)
			if (call_heredoc(parsing_state, env) == FAILURE_BIN_R)
				return (FAILURE_P);
		if (p_result == SUCCESS_P)
			input_tokens = sequence_end;
	}
	if (parsing_state->heredoc_list != NULL)
		ft_lstclear(&(parsing_state->heredoc_list), no_del);
	return (p_result);
}

// static void	print_command_args(t_list *command_args) //テスト用
// {
// 	t_parsed_text *parsed_text;

// 	while (command_args != NULL)
// 	{
// 		parsed_text = (t_parsed_text *)command_args->content;
// 		printf("	command args type: %d\n", parsed_text->type);
// 		printf("		command args: %s\n", parsed_text->str);
// 		command_args = command_args->next;
// 	}
// }

// static void	print_redirection_list(t_list *redirection_list) //テスト用
// {
// 	t_redirection *redirection;

// 	while (redirection_list != NULL)
// 	{
// 		redirection = (t_redirection *)redirection_list->content;
// 		printf("	redirection type: %d\n", redirection->type);
// 		print_file_name(redirection->file_name);
// 		redirection_list = redirection_list->next;
// 	}
// }

// void	print_abs_tree(t_abs_node *abs_tree) //テスト用
// {
// 	if (abs_tree == NULL)
// 		return ;
// 	if (abs_tree->left != NULL)
// 	{
// 		print_abs_tree(abs_tree->left);
// 		printf(":left node\n");
// 	}
// 	if (abs_tree->right != NULL)
// 	{
// 		print_abs_tree(abs_tree->right);
// 		printf(":right node\n");
// 	}
// 	printf("abs node type: %d\n", abs_tree->type);
// 	if (abs_tree->is_subshell)
// 		printf("is_subshell\n");

// 	if (abs_tree->command_args != NULL)
// 	{
// 		printf(" command args: \n");
// 		print_command_args(abs_tree->command_args);
// 	}
// 	if (abs_tree->redirection_list != NULL)
// 	{
// 		printf(" redirection list: \n");
// 		print_redirection_list(abs_tree->redirection_list);
// 	}
// }

t_exit_status	parser(t_list *input_tokens, t_abs_node **abs_tree, t_env env)
{
	t_parsing_state	parsing_state;
	t_parsing		p_result;

	if (input_tokens == NULL)
		return (EXIT_S_FAILURE);
	parsing_state.subshell_depth = 0;
	parsing_state.tree_top_node = NULL;
	parsing_state.working_node = NULL;
	parsing_state.working_node_pos = LEFT;
	parsing_state.heredoc_list = NULL;
	p_result = parse_input(input_tokens, abs_tree, &parsing_state, env);
	// printf("parse result: %d\n", p_result);
	// print_abs_tree(*abs_tree);
	if (p_result == FAILURE_P)
	{
		free_abs_tree(*abs_tree);
		return (EXIT_S_FAILURE);
	}
	else if (p_result == SYNTAX_ERROR_P)
	{
		free_abs_tree(*abs_tree);
		return (EXIT_S_SYNTAX_ERROR);
	}
	else
		return (EXIT_S_SUCCESS);
}
