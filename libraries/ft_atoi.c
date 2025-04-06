/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:49:13 by kharuya           #+#    #+#             */
/*   Updated: 2025/02/18 16:58:45 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_overflow(const char *str, int ans, int sign)
{
	int	digit;

	digit = *str - 48;
	if (sign == 1 && (INT_MAX - digit) / 10 < ans)
		return (INT_MAX);
	if (sign == -1 && (INT_MIN + digit) / 10 > -ans)
		return (INT_MIN);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		ans;
	int		check_overflow;

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
		check_overflow = ft_overflow(str, ans, sign);
		if (check_overflow != 1)
			return (check_overflow);
		ans = (ans * 10) + (*str - 48);
		str++;
	}
	return (sign * ans);
}

// static void	ft_compare(const char *str)
// {
// 	printf("value:'%s' -> ",str);
// 	if(ft_atoi(str) == atoi(str))
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m[KO]\x1b[0m\n");
// }

// int main()
// {
// 	ft_compare("");
// 	ft_compare("-");
// 	ft_compare("+");
// 	ft_compare(" \n\t\v\f\r0");
// 	ft_compare(" \n\t\v\f\r-0");
// 	ft_compare(" \n\t\v\f\r+0");
// 	ft_compare(" \n\t\v\f\r1");
// 	ft_compare(" \n\t\v\f\r-1");
// 	ft_compare(" \n\t\v\f\r+1");
// 	ft_compare(" \n\t\v\f\r7");
// 	ft_compare(" \n\t\v\f\r-7");
// 	ft_compare(" \n\t\v\f\r+7");
// 	ft_compare(" \n\t\v\f\r42");
// 	ft_compare(" \n\t\v\f\r-42");
// 	ft_compare(" \n\t\v\f\ra");
// 	ft_compare(" \n\t\v\f\r!");

// 	//INT_MAX
// 	ft_compare("2147483647");
// 	//INT_MIN
// 	ft_compare("-2147483648");
// 	// UINT_MAX
// 	ft_compare("4294967295");
// 	//LONG_MAX
// 	ft_compare("9223372036854775807");
// 	//LONG_MIN
// 	ft_compare("-9223372036854775808");
// 	//ULONG_MAX
// 	ft_compare("18446744073709551615");
// 	//SIZE_MAX
// 	ft_compare("18446744073709551615");

// 	//INT_MAX + 1
// 	ft_compare("2147483648");
// 	//INT_MIN - 1
// 	ft_compare("-2147483649");
// 	//UINT_MAX + 1
// 	ft_compare("4294967296");
// 	//LONG_MAX + 1
// 	ft_compare("9223372036854775808");
// 	//LONG_MIN - 1
// 	ft_compare("-9223372036854775809");
// 	//ULONG_MAX + 1
// 	ft_compare("18446744073709551616");
// 	//SIZE_MAX + 1
// 	ft_compare("18446744073709551616");

// 	//INT_MAX - 1
// 	ft_compare("2147483646");
// 	//INT_MIN + 1
// 	ft_compare("-2147483647");
// 	//UINT_MAX - 1
// 	ft_compare("4294967294");
// 	//LONG_MAX - 1
// 	ft_compare("9223372036854775806");
// 	//LONG_MIN + 1
// 	ft_compare("-9223372036854775807");
// 	//ULONG_MAX - 1
// 	ft_compare("18446744073709551614");
// 	//SIZE_MAX - 1
// 	ft_compare("18446744073709551614");

// 	//Many zeros
// 	ft_compare("000000000000000000008");
// 	ft_compare("-000000000000000000008");
// 	ft_compare("+000000000000000000008");
// }