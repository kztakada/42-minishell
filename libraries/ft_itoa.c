/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:56:06 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:23:28 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_zero_handle(void)
{
	char	*ans;

	ans = (char *)malloc(sizeof(char) * 2);
	if (!ans)
		return (NULL);
	ans[0] = '0';
	ans[1] = '\0';
	return (ans);
}

static size_t	ft_count_digits(int n)
{
	int	res_sign;
	int	res_digit;

	res_sign = 0;
	res_digit = 0;
	if (n < 0)
		res_sign++;
	while (n != 0)
	{
		n /= 10;
		res_digit++;
	}
	return (res_sign + res_digit);
}

static int	ft_divide_count(int count, int i)
{
	int	divide;
	int	multiplier;

	divide = 1;
	multiplier = count - i - 1;
	while (multiplier-- > 0)
		divide *= 10;
	return (divide);
}

static char	*ft_itoa_make(char *ans, int n,	size_t count)
{
	size_t	i;
	int		divide;
	int		digit;

	i = 0;
	if (n < 0)
		ans[i++] = '-';
	divide = ft_divide_count(count, i);
	while (divide > 0)
	{
		digit = n / divide;
		if (digit < 0)
			digit *= -1;
		ans[i++] = digit + '0';
		n = n % divide;
		divide /= 10;
	}
	ans[i] = '\0';
	return (ans);
}

char	*ft_itoa(int n)
{
	size_t	count;
	char	*ans;

	if (n == 0)
		return (ft_zero_handle());
	count = ft_count_digits(n);
	ans = (char *)malloc(sizeof(char) * (count + 1));
	if (!ans)
		return (NULL);
	return (ft_itoa_make(ans, n, count));
}

// static void check_itoa(char *res_ft,char *expected)
// {
// 	printf("res_ft=%s expected=%s",res_ft,expected);
// 	if(strcmp(res_ft,expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_itoa(ft_itoa(0), "0");
// 	check_itoa(ft_itoa(-0), "0");
// 	check_itoa(ft_itoa(+0), "0");
// 	check_itoa(ft_itoa(1),"1");
// 	check_itoa(ft_itoa(-1),"-1");
// 	check_itoa(ft_itoa(+1),"1");
// 	check_itoa(ft_itoa(7),"7");
// 	check_itoa(ft_itoa(-7),"-7");
// 	check_itoa(ft_itoa(+7),"7");
// 	check_itoa(ft_itoa(42), "42");
// 	check_itoa(ft_itoa(-42), "-42");
// 	check_itoa(ft_itoa(+42), "42");
// 	//INT_MAX
// 	check_itoa(ft_itoa(2147483647),"2147483647");
// 	//INT_MIN
// 	check_itoa(ft_itoa(-2147483648),"-2147483648");
// 	//INT_MAX - 1
// 	check_itoa(ft_itoa(2147483646), "2147483646");
// 	//INT_MIN + 1
// 	check_itoa(ft_itoa(-2147483647), "-2147483647");
// }