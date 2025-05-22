/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_test_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:18:59 by katakada          #+#    #+#             */
/*   Updated: 2025/05/22 23:28:03 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expanding.h"
#include "parsing.h"

#ifdef __GNUC__
# define UNUSED __attribute__((unused))
#else
# define UNUSED
#endif

// for expander test		**************************************************//
void UNUSED	print_expanding_token_list(t_list *expanding_tokens)
{
	t_expanding_token	*expanding_token;

	while (expanding_tokens != NULL)
	{
		expanding_token = (t_expanding_token *)expanding_tokens->content;
		if (expanding_token->type == ET_UNQUOTED_STR)
			printf("ET_UNQUOTED_STR: %s\n", expanding_token->str);
		else if (expanding_token->type == ET_QUOTED_STR)
			printf("ET_QUOTED_STR: %s\n", expanding_token->str);
		else if (expanding_token->type == ET_DEATH_DOLLAR)
			printf("ET_DEATH_DOLLAR: %s\n", "$");
		else if (expanding_token->type == ET_WILDCARD)
			printf("ET_WILDCARD: %s\n", "*");
		else if (expanding_token->type == ET_SEPARATOR)
			printf("ET_SEPARATOR: %s\n", "/");
		else
			printf("Unknown type\n");
		expanding_tokens = expanding_tokens->next;
	}
}

void UNUSED	print_str_list(char **str_list)
{
	int	i;

	i = 0;
	while (str_list[i] != NULL)
	{
		printf("%s\n", str_list[i]);
		i++;
	}
}

void UNUSED	print_expanded_file_names(t_list *redirections)
{
	t_list			*current_redirection;
	t_redirection	*redirection;

	current_redirection = redirections;
	while (current_redirection != NULL)
	{
		redirection = (t_redirection *)current_redirection->content;
		printf("Expanded file name: %s\n", redirection->expanded_file_name);
		current_redirection = current_redirection->next;
	}
}

// for call_heredoc test **************************************************//
void UNUSED	all_get_line(int fd) //テスト用
{
	char *line;

	printf("all_get_line fd:%d\n", fd);
	while (TRUE)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		printf("%s", line);
		free(line);
	}
}

// for parser test ******************************************************//
static void UNUSED	print_file_name_words(t_list *file_name_words) //テスト用
{
	t_parsed_word *parsed_word;

	while (file_name_words != NULL)
	{
		parsed_word = (t_parsed_word *)file_name_words->content;
		printf("		file name type: %d\n", parsed_word->type);
		printf("		file name: %s\n", parsed_word->str);
		file_name_words = file_name_words->next;
	}
}

static void UNUSED	print_heredoc_list(t_list *heredoc_list) //テスト用
{
	t_redirection *redirection;

	while (heredoc_list != NULL)
	{
		redirection = (t_redirection *)heredoc_list->content;
		printf("heredoc type: %d\n", redirection->type);
		print_file_name_words(redirection->file_name_words);
		heredoc_list = heredoc_list->next;
	}
}

static void UNUSED	print_cmd_words(t_list *cmd_words) //テスト用
{
	t_parsed_word *parsed_word;

	while (cmd_words != NULL)
	{
		parsed_word = (t_parsed_word *)cmd_words->content;
		printf("	command args type: %d\n", parsed_word->type);
		printf("		command args: %s\n", parsed_word->str);
		cmd_words = cmd_words->next;
	}
}

static void UNUSED	print_redirections(t_list *redirections) //テスト用
{
	t_redirection *redirection;

	while (redirections != NULL)
	{
		redirection = (t_redirection *)redirections->content;
		printf("	redirection type: %d\n", redirection->type);
		print_file_name_words(redirection->file_name_words);
		redirections = redirections->next;
	}
}

void UNUSED	print_abs_tree(t_abs_node *abs_tree) //テスト用
{
	if (abs_tree == NULL)
		return ;
	if (abs_tree->left != NULL)
	{
		print_abs_tree(abs_tree->left);
		printf(":left node\n");
	}
	if (abs_tree->right != NULL)
	{
		print_abs_tree(abs_tree->right);
		printf(":right node\n");
	}
	printf("abs node type: %d\n", abs_tree->type);
	if (abs_tree->is_subshell)
		printf("is_subshell\n");

	if (abs_tree->cmd_words != NULL)
	{
		printf(" command args: \n");
		print_cmd_words(abs_tree->cmd_words);
	}
	if (abs_tree->redirections != NULL)
	{
		printf(" redirection list: \n");
		print_redirections(abs_tree->redirections);
	}
}

// トークナイザーの出力テスト用 ********************************************
void UNUSED	print_token_list(t_list *token_list)
{
	t_list	*current;
	t_token	*token;

	current = token_list;
	while (current)
	{
		token = (t_token *)current->content;
		printf("Token type: %d, count:%zu, content: %s\n", token->type,
			ft_strlen(token->value), token->value);
		current = current->next;
	}
}

// envの出力テスト用 *****************************************************
void UNUSED	print_env_list(t_list *env_vars)
{
	t_list		*current;
	t_env_var	*env_var;

	current = env_vars;
	while (current)
	{
		env_var = (t_env_var *)current->content;
		printf("Env var name: %s, value: %s\n", env_var->name, env_var->value);
		current = current->next;
	}
}
