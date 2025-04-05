/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:54:27 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:24:09 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}

// #include <ctype.h>

// static void check_alnum(int i,int j)
// {
// 	printf("i=%d j=%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_alnum(ft_isalnum('a'), isalnum('a'));
// 	check_alnum(ft_isalnum('a' - 1), isalnum('a' - 1));
// 	check_alnum(ft_isalnum('a' + 1), isalnum('a' + 1));
// 	check_alnum(ft_isalnum('z'), isalnum('z'));
// 	check_alnum(ft_isalnum('z' - 1), isalnum('z' - 1));
// 	check_alnum(ft_isalnum('z' + 1), isalnum('z' + 1));
// 	check_alnum(ft_isalnum('A'), isalnum('A'));
// 	check_alnum(ft_isalnum('A' - 1), isalnum('A' - 1));
// 	check_alnum(ft_isalnum('A' + 1), isalnum('A' + 1));
// 	check_alnum(ft_isalnum('Z'), isalnum('Z'));
// 	check_alnum(ft_isalnum('Z' - 1), isalnum('Z' - 1));
// 	check_alnum(ft_isalnum('Z' + 1), isalnum('Z' + 1));
// 	check_alnum(ft_isalnum('a' + 256), isalnum('a' + 256));
// 	check_alnum(ft_isalnum('a' - 256), isalnum('a' - 256));
// 	check_alnum(ft_isalnum('a' + 1), isalnum('a' + 1));
// 	check_alnum(ft_isalnum('0'), isalnum('0'));
// 	check_alnum(ft_isalnum('0' - 1), isalnum('0' - 1));
// 	check_alnum(ft_isalnum('0' + 1), isalnum('0' + 1));
// 	check_alnum(ft_isalnum('9'), isalnum('9'));
// 	check_alnum(ft_isalnum('9' - 1), isalnum('9' - 1));
// 	check_alnum(ft_isalnum('9' + 1), isalnum('9' + 1));
// 	check_alnum(ft_isalnum('!'), isalnum('!'));
// 	check_alnum(ft_isalnum('{'), isalnum('}'));
// 	check_alnum(ft_isalnum('~'), isalnum('~'));
// 	//zero
// 	check_alnum(ft_isalnum(0), isalnum(0));
// 	//INI_MAX
// 	check_alnum(ft_isalnum(INT_MAX), isalnum(INT_MAX));
// 	//INT_MIN
// 	check_alnum(ft_isalnum(INT_MIN), isalnum(INT_MIN));
// }