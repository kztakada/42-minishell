/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 20:01:43 by katakada          #+#    #+#             */
/*   Updated: 2025/05/17 14:30:24 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDING_H
# define EXPANDING_H

# include "t_minishell.h"

// t_expanded_word **********************************************
typedef enum e_expand_word_type
{
	EW_WILDCARD,
	EW_SEPARATOR,
	EW_EXPANDED,
}					t_e_word_type;
typedef struct s_expanded_word
{
	t_e_word_type	type;
	char			*str;
}					t_expanded_word;

// expander.c
t_exit_status		expander(t_abs_node *abs_tree, t_env env);
char				*get_envlst_val(char *name, t_list *envlst);

#endif
