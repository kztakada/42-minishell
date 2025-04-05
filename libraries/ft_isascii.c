/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:54:54 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:23:52 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

// #include <ctype.h>

// static void check_isascii(int i,int j)
// {
// 	printf("i=%d j=%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_isascii(ft_isascii('a'), isascii('b'));
// 	check_isascii(ft_isascii('a' - 1), isascii('a' - 1));
// 	check_isascii(ft_isascii('a' + 1), isascii('a' + 1));
// 	check_isascii(ft_isascii('z'), isascii('z'));
// 	check_isascii(ft_isascii('z' - 1), isascii('z' - 1));
// 	check_isascii(ft_isascii('z' + 1), isascii('z' + 1));
// 	check_isascii(ft_isascii('A'), isascii('A'));
// 	check_isascii(ft_isascii('A' - 1), isascii('A' - 1));
// 	check_isascii(ft_isascii('A' + 1), isascii('A' + 1));
// 	check_isascii(ft_isascii('Z'), isascii('Z'));
// 	check_isascii(ft_isascii('Z' - 1), isascii('Z' - 1));
// 	check_isascii(ft_isascii('Z' + 1), isascii('Z' + 1));
// 	check_isascii(ft_isascii('a' + 256), isascii('a' + 256));
// 	check_isascii(ft_isascii('a' - 256), isascii('a' - 256));
// 	check_isascii(ft_isascii('a' + 1), isascii('a' + 1));
// 	check_isascii(ft_isascii('!'), isascii('!'));
// 	check_isascii(ft_isascii('{'), isascii('}'));
// 	check_isascii(ft_isascii('~'), isascii('~'));
// 	//zero
// 	check_isascii(ft_isascii(0), isascii(0));
// 	//INI_MAX
// 	check_isascii(ft_isascii(INT_MAX), isascii(INT_MAX));
// 	//21. INT_MIN
// 	check_isascii(ft_isascii(INT_MIN), isascii(INT_MIN));
// }