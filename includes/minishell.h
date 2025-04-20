/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:55:38 by katakada          #+#    #+#             */
/*   Updated: 2025/04/18 20:15:45 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./for_test.h" // for test
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <termios.h>

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1,
}			t_bool;

// error messages
# define ERROR_MALLOC "Error: Memory allocation failed\n"

// for dictionary
// dictionary format: 1st char is separator in the dictionary
# define OPERATORS_DICT " << >> && || | < > ( )"
# define SPACE_DICT "_ _\t_\n_\v_\f_\r"
# define NUM_DICT " 0 1 2 3 4 5 6 7 8 9"
# define QUOTE_DICT " \" ' "
# define NO_MATCH_DICT "no match in dictionary"
# define INVALID_DICT "invalid dictionary"
# define INVALID_SUBJECT "invalid subject"

typedef struct s_dict_out
{
	t_bool	in_d;
	int		d_index;
	char	*nx_str;
	char	*error;
}			t_dict_out;

// dictionary.c
t_dict_out	lookup_dict(char *subject, char *dict);
char		*get_dict_word(int d_index, char *dict);

#endif