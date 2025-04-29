/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:53:27 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/24 03:44:15 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/h_minishell.h"

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

static void	digit_err_msg(char *arg)
{
	ft_putendl_fd("exit", 2);
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return ;
}

static void	format_err_msg(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("bash: exit: too many arguments", 2);
	return ;
}

static int	get_exit_s(char *arg)
{
	int		num;
	int		overflow_flag;

	overflow_flag = false;
	num = ft_atol(arg, &overflow_flag);
	if (overflow_flag)
	{
		digit_err_msg(arg);
		return (255);
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

int	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_s;

	exit_s = minishell->exit_s;
	if (args[1])
	{
		if (args[2])
		{
			format_err_msg();
			exit(255);
		}
		else if (!is_digit(args[1]))
		{
			digit_err_msg(args[1]);
			exit(255);
		}
		else
			exit(get_exit_s(args[1]));
	}
	exit(exit_s);
}
