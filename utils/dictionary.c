/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:10:10 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 23:04:28 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_dict_out	init_dict_out(void)
{
	t_dict_out	d_out;

	d_out.in_d = FALSE;
	d_out.d_index = -1;
	d_out.nx_str = NULL;
	d_out.error = NULL;
	return (d_out);
}

static t_dict_out	handle_input_dict_error(char *subject, char *dict,
		char *separator, char **dict_nx_str)
{
	t_dict_out	d_out;

	d_out = init_dict_out();
	if (!subject)
		return (d_out.error = INVALID_SUBJECT, d_out);
	if (!*subject)
		return (d_out.error = NO_MATCH_DICT, d_out);
	if (!dict || !*dict)
		return (d_out.error = INVALID_DICT, d_out);
	*separator = *dict;
	*dict_nx_str = dict + 1;
	if (!**dict_nx_str || **dict_nx_str == *separator)
		return (d_out.error = INVALID_DICT, d_out);
	d_out.d_index = 0;
	d_out.nx_str = subject;
	return (d_out);
}

static t_dict_out	search_in_dict(t_dict_out d_out, char *dict_nx_str,
		char separator)
{
	char	*comp;
	int		comp_char_count;

	while (*dict_nx_str)
	{
		comp = dict_nx_str;
		comp_char_count = 0;
		while (*comp && *comp != separator)
		{
			comp_char_count++;
			comp++;
		}
		if (ft_strncmp(d_out.nx_str, dict_nx_str, comp_char_count) == 0)
		{
			d_out.nx_str += comp_char_count;
			d_out.in_d = TRUE;
			return (d_out);
		}
		dict_nx_str += comp_char_count;
		while (*dict_nx_str && *dict_nx_str == separator)
			dict_nx_str++;
		d_out.d_index++;
	}
	return (d_out);
}

// Function that returns the index number of the corresponding
// dictionary word and the string of the next dictionary word
// when a dictionary string and dictionary are assigned as arguments
t_dict_out	lookup_dict(char *subject, char *dict)
{
	char		*dict_nx_str;
	char		separator;
	t_dict_out	d_out;

	dict_nx_str = NULL;
	separator = 0;
	d_out = handle_input_dict_error(subject, dict, &separator, &dict_nx_str);
	if (d_out.d_index == -1)
		return (d_out);
	d_out = search_in_dict(d_out, dict_nx_str, separator);
	if (d_out.in_d == FALSE)
	{
		d_out.d_index = -1;
		d_out.error = NO_MATCH_DICT;
	}
	return (d_out);
}

// Function that returns a string that duplicates the corresponding
// dictionary word by ft_substr when the index number and dictionary
// are assigned to the argument
char	*get_dict_word(int d_index, char *dict)
{
	char	*dict_nx_str;
	char	separator;
	int		i;

	if (d_index < 0 || d_index > (int)ft_strlen(dict))
		return (NULL);
	i = 0;
	separator = dict[0];
	dict++;
	dict_nx_str = dict;
	while (*dict_nx_str)
	{
		dict = dict_nx_str;
		while (*dict_nx_str && *dict_nx_str != separator)
			dict_nx_str++;
		if (i == d_index)
			return (ft_substr(dict, 0, dict_nx_str - dict));
		while (*dict_nx_str && *dict_nx_str == separator)
			dict_nx_str++;
		i++;
	}
	return (NULL);
}
