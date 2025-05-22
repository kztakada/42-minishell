#ifndef FOR_TEST_PRINT_H
# define FOR_TEST_PRINT_H

# include "minishell.h"
void	print_expanding_token_list(t_list *expanding_tokens);
void	print_str_list(char **str_list);
void	print_expanded_file_names(t_list *redirections);
void	all_get_line(int fd);
void	print_abs_tree(t_abs_node *abs_tree);
void	print_token_list(t_list *token_list);
void	print_env_list(t_list *env_vars);
#endif