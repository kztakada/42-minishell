/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:30 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:10:15 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c > 255 || c < 0))
		return (c);
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

// #include <ctype.h>

// static void check_toupper(int i,int j)
// {
// 	printf("%d,%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	check_toupper(ft_toupper('a'), toupper('a'));
// 	check_toupper(ft_toupper('a' - 1), toupper('a' - 1));
// 	check_toupper(ft_toupper('a' + 1), toupper('a' + 1));
// 	check_toupper(ft_toupper('z'), toupper('z'));
// 	check_toupper(ft_toupper('z' - 1), toupper('z' - 1));
// 	check_toupper(ft_toupper('z' + 1), toupper('z' + 1));
// 	check_toupper(ft_toupper('A'), toupper('A'));
// 	check_toupper(ft_toupper('A' - 1), toupper('A' - 1));
// 	check_toupper(ft_toupper('A' + 1), toupper('A' + 1));
// 	check_toupper(ft_toupper('Z'), toupper('Z'));
// 	check_toupper(ft_toupper('Z' - 1), toupper('Z' - 1));
// 	check_toupper(ft_toupper('Z' + 1), toupper('Z' + 1));
// 	check_toupper(ft_toupper('a' + 256), toupper('a' + 256));
// 	check_toupper(ft_toupper('a' - 256), toupper('a' - 256));
// 	check_toupper(ft_toupper('a' + 1), toupper('a' + 1));
// 	check_toupper(ft_toupper('!'), toupper('!'));
// 	check_toupper(ft_toupper('{'), toupper('{'));
// 	check_toupper(ft_toupper('~'), toupper('~'));
// 	//zero
// 	check_toupper(ft_toupper(0), toupper(0));
// 	//INI_MAX
// 	check_toupper(ft_toupper(INT_MAX), toupper(INT_MAX));
// 	//INT_MIN
// 	check_toupper(ft_toupper(INT_MIN), toupper(INT_MIN));
// }