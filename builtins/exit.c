/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:27 by kharuya           #+#    #+#             */
/*   Updated: 2025/05/20 02:36:56 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

static	int	is_digit(char *arg)
{
	while (*arg)
	{
		if (*arg < '0' || *arg > '9')
			return (0);
		arg++;
	}
	return (1);
}

static int	get_exit_s(char *arg)
{
	int		num;
	int		overflow_flag;

	overflow_flag = false;
	num = ft_atol(arg, &overflow_flag);
	if (overflow_flag)
	{
		exit_err_msg_digit(arg);
		return (EXIT_S_OUT_OF_RANGE);
	}
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

int	ft_exit(char **args, t_exit_status exit_s)
{
	if (args[1])
	{
		if (!is_digit(args[1]))
		{
			exit_err_msg_digit(args[1]);
			exit(EXIT_S_OUT_OF_RANGE);
		}
		else if (args[2])
		{
			exit_err_msg_format();
			exit(EXIT_S_FAILURE);
		}
		else
			exit(get_exit_s(args[1]));
	}
	exit(exit_s);
}
