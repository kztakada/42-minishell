/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:49:47 by katakada          #+#    #+#             */
/*   Updated: 2025/04/27 19:18:00 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_minishell.h"

// トークナイザーの出力テスト用
void	print_token_list(t_list *token_list)
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

// envの出力テスト用
void	print_env_list(t_list *env_lists)
{
	t_list		*current;
	t_env_var	*env_var;

	current = env_lists;
	while (current)
	{
		env_var = (t_env_var *)current->content;
		printf("Env var name: %s, value: %s\n", env_var->name, env_var->value);
		current = current->next;
	}
}

static char	*extract_env_var_name(char *env_var_source, int *is_error)
{
	char	*var_name;
	int		i;

	i = 0;
	var_name = NULL;
	while (env_var_source[i] && env_var_source[i] != '=')
		i++;
	var_name = ft_substr(env_var_source, 0, i);
	if (var_name == NULL)
		*is_error = TRUE;
	return (var_name);
}

static char	*extract_env_var_value(char *env_var_source, int *is_error)
{
	char	*var_value;
	int		var_value_len;
	int		i;

	i = 0;
	var_value = NULL;
	while (env_var_source[i] && env_var_source[i] != '=')
		i++;
	if (env_var_source[i] == '=')
	{
		i++;
		var_value_len = ft_strlen(env_var_source) - i;
		var_value = ft_substr(env_var_source, i, var_value_len);
		if (var_value == NULL)
			*is_error = TRUE;
	}
	return (var_value);
}

static t_env_var	*get_env_var(char *env_var_source)
{
	char		*env_var_name;
	char		*env_var_value;
	t_env_var	*env_var;
	int			is_error;

	is_error = FALSE;
	env_var_name = extract_env_var_name(env_var_source, &is_error);
	env_var_value = extract_env_var_value(env_var_source, &is_error);
	if (!env_var_name || is_error)
		return (NULL);
	env_var = malloc(sizeof(t_env_var));
	if (!env_var)
	{
		free(env_var_name);
		free(env_var_value);
		return (NULL);
	}
	env_var->name = env_var_name;
	env_var->value = env_var_value;
	return (env_var);
}

void	free_env_var(void *env_var)
{
	t_env_var	*to_free_object;

	to_free_object = (t_env_var *)env_var;
	if (to_free_object)
	{
		free(to_free_object->name);
		free(to_free_object->value);
		free(to_free_object);
	}
}

static t_list	**set_env_ver_to_list(t_list **env_lists, t_env_var *env_var)
{
	t_list	*new_env_list;

	new_env_list = ft_lstnew(env_var);
	if (!new_env_list)
	{
		free_env_var((void *)env_var);
		return (NULL);
	}
	ft_lstadd_back(env_lists, new_env_list);
	return (env_lists);
}

t_list	*init_envlst(char **env)
{
	int			i;
	t_list		*env_lists;
	t_env_var	*env_var;

	if (!env)
		return (NULL);
	i = 0;
	env_lists = NULL;
	while (env[i])
	{
		env_var = get_env_var(env[i]);
		if (!env_var)
		{
			ft_lstclear(&env_lists, free_env_var);
			return (NULL);
		}
		if (!set_env_ver_to_list(&env_lists, env_var))
		{
			ft_lstclear(&env_lists, free_env_var);
			return (NULL);
		}
		i++;
	}
	return (env_lists);
}

static t_bool	safe_add_history(char *input)
{
	if (input == NULL)
		return (exit(EXIT_FAILURE), FALSE);
	if (*input)
		add_history(input);
	else
	{
		free(input);
		return (FALSE);
	}
	return (TRUE);
}

static int	execute_command(char *input)
{
	t_list		*token_list;
	t_list		*abs_tree;
	static int	exit_status = 0;

	// TODO: lexerでエラーした時にexit_statusは何番を返せば良いか？
	token_list = NULL;
	exit_status = lexer(input, &token_list);
	free(input);
	if (exit_status != 0)
		return (FAILURE);
	// print_token_list(token_list); // テスト用
	abs_tree = NULL;
	exit_status = parse(token_list, &abs_tree); //未実装
	ft_lstclear(&token_list, free_token);
	if (exit_status != 0)
		return (FAILURE);
	ft_lstclear(&abs_tree, free_abs_node);
	// exec_(abs_tree); //未実装
	return (SUCCESS);
}

int	app_main(int argc, char **argv, char **env)
{
	const int	is_interactive = isatty(STDIN_FILENO) && isatty(STDOUT_FILENO);
	char		*input;
	char		*newline;
	t_list		*env_lists;

	(void)argc;
	(void)argv;
	env_lists = init_envlst(env);
	// print_env_list(env_lists); // テスト用
	ft_lstclear(&env_lists, free_env_var);
	if (is_interactive)
	{
		while (TRUE)
		{
			input = readline(PROMPT);
			if (safe_add_history(input) == FALSE)
				continue ;
			execute_command(input);
		}
	}
	else
	{
		input = NULL;
		input = get_next_line(STDIN_FILENO);
		// TODO: 複数行実行した場合、出力パイプがどうなるか確認
		// 複数行処理やめて、１行の未処理対応にするか検討すること
		while (input != NULL)
		{
			newline = ft_strchr(input, '\n');
			if (newline)
				*newline = '\0';
			// printf("%s\n", input); // テスト用
			execute_command(input);
			input = get_next_line(STDIN_FILENO);
		}
		free(input);
	}
	return (0);
}

#ifndef TEST

int	main(int argc, char **argv, char **env)
{
	return (app_main(argc, argv, env));
}
#endif // TEST