/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 03:23:44 by kharuya           #+#    #+#             */
/*   Updated: 2025/04/24 03:43:00 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_overflow(const char *str, long ans, long sign, int *overflow)
{
	long	digit;

	digit = *str - 48;
	if (sign == 1 && (LONG_MAX - digit) / 10 < ans)
	{
		*overflow = 1;
		return (LONG_MAX);
	}
	if (sign == -1 && (LONG_MIN + digit) / 10 > -ans)
	{
		*overflow = 1;
		return (LONG_MIN);
	}
	else
		return (1);
}

long	ft_atol(const char *str, int *overflow)
{
	long	sign;
	long	ans;
	long	check_overflow;

	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	ans = 0;
	while (*str >= '0' && *str <= '9')
	{
		check_overflow = ft_overflow(str, ans, sign, overflow);
		if (check_overflow != 1)
			return (check_overflow);
		ans = (ans * 10) + (*str - 48);
		str++;
	}
	return (sign * ans);
}
