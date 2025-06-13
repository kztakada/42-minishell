/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env__shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 00:59:37 by katakada          #+#    #+#             */
/*   Updated: 2025/06/13 22:12:45 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_warning_shlvl_value(int shlvl_value)
{
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putnbr_fd(shlvl_value, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

t_bool	has_numeric_chars(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (FALSE);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	has_only_numbers(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	get_shlvl_value(t_list *env_list)
{
	char	*shlvl_str;
	int		shlvl_value;

	shlvl_str = get_env_value(env_list, "SHLVL");
	if (shlvl_str == NULL)
		return (1);
	if (ft_strcmp(shlvl_str, "") == 0)
		return (1);
	if (!has_numeric_chars(shlvl_str))
		return (1);
	if (!has_only_numbers(shlvl_str))
		return (1);
	shlvl_value = ft_atoi(shlvl_str);
	if (shlvl_value == INT_MAX || shlvl_value < 0)
		return (0);
	if (shlvl_value <= 998)
		return (shlvl_value + 1);
	put_warning_shlvl_value(shlvl_value + 1);
	return (1);
}

t_binary_result	init_env_shlvl(t_list **env_list)
{
	int		shlvl_value;
	char	*shlvl_str;

	if (is_env_exist(*env_list, "SHLVL"))
	{
		shlvl_value = get_shlvl_value(*env_list);
		shlvl_str = ft_itoa(shlvl_value);
		if (shlvl_str == NULL)
			return (perror(ERROR_MALLOC), FAILURE_BIN_R);
		if (update_env_value(env_list, "SHLVL", shlvl_str) == EXIT_S_FAILURE)
			return (free(shlvl_str), FAILURE_BIN_R);
		free(shlvl_str);
	}
	else
	{
		if (create_add_new_env(env_list, "SHLVL", "1") == EXIT_S_FAILURE)
			return (FAILURE_BIN_R);
	}
	return (SUCCESS_BIN_R);
}
