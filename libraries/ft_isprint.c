/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:46:02 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:23:37 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

// #include <ctype.h>

// static void check_isprint(int i,int j)
// {
// 	printf("i=%d j=%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_isprint(ft_isprint('a'), isprint('a'));
// 	check_isprint(ft_isprint('a' - 1), isprint('a' - 1));
// 	check_isprint(ft_isprint('a' + 1), isprint('a' + 1));
// 	check_isprint(ft_isprint('z'), isprint('z'));
// 	check_isprint(ft_isprint('z' - 1), isprint('z' - 1));
// 	check_isprint(ft_isprint('z' + 1), isprint('z' + 1));
// 	check_isprint(ft_isprint('A'), isprint('A'));
// 	check_isprint(ft_isprint('A' - 1), isprint('A' - 1));
// 	check_isprint(ft_isprint('A' + 1), isprint('A' + 1));
// 	check_isprint(ft_isprint('Z'), isprint('Z'));
// 	check_isprint(ft_isprint('Z' - 1), isprint('Z' - 1));
// 	check_isprint(ft_isprint('Z' + 1), isprint('Z' + 1));
// 	check_isprint(ft_isprint('a' + 256), isprint('a' + 256));
// 	check_isprint(ft_isprint('a' - 256), isprint('a' - 256));
// 	check_isprint(ft_isprint('a' + 1), isprint('a' + 1));
// 	check_isprint(ft_isprint('0'), isprint('0'));
// 	check_isprint(ft_isprint('0' - 1), isprint('0' - 1));
// 	check_isprint(ft_isprint('0' + 1), isprint('0' + 1));
// 	check_isprint(ft_isprint('9'), isprint('9'));
// 	check_isprint(ft_isprint('9' - 1), isprint('9' - 1));
// 	check_isprint(ft_isprint('9' + 1), isprint('9' + 1));
// 	check_isprint(ft_isprint('!'), isprint('!'));
// 	check_isprint(ft_isprint('{'), isprint('}'));
// 	check_isprint(ft_isprint('~'), isprint('~'));
// 	//zero
// 	check_isprint(ft_isprint(0), isprint(0));
// 	//INI_MAX
// 	check_isprint(ft_isprint(INT_MAX), isprint(INT_MAX));
// 	//INT_MIN
// 	check_isprint(ft_isprint(INT_MIN), isprint(INT_MIN));
// }