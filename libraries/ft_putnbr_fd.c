/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:57:50 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 08:42:11 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digits(int n)
{
	int	res_digit;

	res_digit = 0;
	while (n != 0)
	{
		n /= 10;
		res_digit++;
	}
	return (res_digit);
}

static int	ft_divide_count(int count)
{
	int	divide;
	int	multiplier;

	divide = 1;
	multiplier = count - 1;
	while (multiplier-- > 0)
		divide *= 10;
	return (divide);
}

void	ft_putnbr_fd(int n, int fd)
{
	size_t	count;
	int		digit;
	int		divide;
	char	c;

	if (n < 0)
		write(fd, "-", 1);
	count = ft_count_digits(n);
	divide = ft_divide_count(count);
	while (divide > 0)
	{
		digit = n / divide;
		if (digit < 0)
			digit *= -1;
		n %= divide;
		divide /= 10;
		c = digit + '0';
		write(fd, &c, 1);
	}
}

// int main()
// {
// 	ft_putnbr_fd(0,1);
// 	printf("\n");
// 	ft_putnbr_fd(INT_MAX,1);
// 	printf("\n");
// 	ft_putnbr_fd(INT_MIN,1);
// 	printf("\n");
// }