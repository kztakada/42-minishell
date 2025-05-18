#ifndef FOR_TEST_PARSING_H
# define FOR_TEST_PARSING_H

# include "t_minishell.h"

void	all_get_line(int fd);
void	print_abs_tree(t_abs_node *abs_tree);
void	print_token_list(t_list *token_list);
void	print_env_list(t_list *env_vars);
#endif