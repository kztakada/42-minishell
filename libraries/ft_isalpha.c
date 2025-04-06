/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:54:43 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:24:00 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// #include <ctype.h>

// static void check_isalpha(int i,int j)
// {
// 	printf("i=%d j=%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_isalpha(ft_isalpha('a'), isalpha('b'));
// 	check_isalpha(ft_isalpha('a' - 1), isalpha('a' - 1));
// 	check_isalpha(ft_isalpha('a' + 1), isalpha('a' + 1));
// 	check_isalpha(ft_isalpha('z'), isalpha('z'));
// 	check_isalpha(ft_isalpha('z' - 1), isalpha('z' - 1));
// 	check_isalpha(ft_isalpha('z' + 1), isalpha('z' + 1));
// 	check_isalpha(ft_isalpha('A'), isalpha('A'));
// 	check_isalpha(ft_isalpha('A' - 1), isalpha('A' - 1));
// 	check_isalpha(ft_isalpha('A' + 1), isalpha('A' + 1));
// 	check_isalpha(ft_isalpha('Z'), isalpha('Z'));
// 	check_isalpha(ft_isalpha('Z' - 1), isalpha('Z' - 1));
// 	check_isalpha(ft_isalpha('Z' + 1), isalpha('Z' + 1));
// 	check_isalpha(ft_isalpha('a' + 256), isalpha('a' + 256));
// 	check_isalpha(ft_isalpha('a' - 256), isalpha('a' - 256));
// 	check_isalpha(ft_isalpha('a' + 1), isalpha('a' + 1));
// 	check_isalpha(ft_isalpha('!'), isalpha('!'));
// 	check_isalpha(ft_isalpha('{'), isalpha('}'));
// 	check_isalpha(ft_isalpha('~'), isalpha('~'));
// 	//zero
// 	check_isalpha(ft_isalpha(0), isalpha(0));
// 	//INI_MAX
// 	check_isalpha(ft_isalpha(INT_MAX), isalpha(INT_MAX));
// 	//21. INT_MIN
// 	check_isalpha(ft_isalpha(INT_MIN), isalpha(INT_MIN));
// }