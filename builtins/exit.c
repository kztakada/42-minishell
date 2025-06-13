/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:27 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/14 02:30:20 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static t_bool	is_digit(char *arg)
{
	if (!arg || *arg == '\0')
		return (FALSE);
	if (!has_numeric_chars(arg))
		return (FALSE);
	if (!has_only_numbers(arg))
		return (FALSE);
	return (TRUE);
}

static int	get_exit_s(char *arg)
{
	int	num;
	int	overflow_flag;

	overflow_flag = false;
	num = ft_atol(arg, &overflow_flag);
	if (overflow_flag)
		return (exit_err_msg_digit(arg));
	else if (num >= 0 && num < 255)
		return (num);
	else if (num > 255)
		return (num % 256);
	else
	{
		if (-255 > num)
			num %= 256;
		return (256 + num);
	}
}

void	ft_exit(char **args, t_env *env, t_exit_status exit_s)
{
	int	status;

	status = exit_s;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1])
	{
		if (!is_digit(args[1]) || ft_strcmp("", args[1]) == 0)
			status = exit_err_msg_digit(args[1]);
		else if (args[2])
			status = exit_err_msg_format();
		else
			status = get_exit_s(args[1]);
	}
	clean_and_exit(status, env);
}
