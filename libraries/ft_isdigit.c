/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 21:54:59 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:23:45 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

// #include <ctype.h>

// static void check_isdigit(int i,int j)
// {
// 	printf("i=%d j=%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_isdigit(ft_isdigit('0'), isdigit('0'));
// 	check_isdigit(ft_isdigit('0' - 1), isdigit('0' - 1));
// 	check_isdigit(ft_isdigit('0' + 1), isdigit('0' + 1));
// 	check_isdigit(ft_isdigit('9'), isdigit('9'));
// 	check_isdigit(ft_isdigit('9' - 1), isdigit('9' - 1));
// 	check_isdigit(ft_isdigit('9' + 1), isdigit('9' + 1));
// 	check_isdigit(ft_isdigit('!'), isdigit('!'));
// 	check_isdigit(ft_isdigit('{'), isdigit('}'));
// 	check_isdigit(ft_isdigit('~'), isdigit('~'));
// 	//zero
// 	check_isdigit(ft_isdigit(0), isdigit(0));
// 	//INI_MAX
// 	check_isdigit(ft_isdigit(INT_MAX), isdigit(INT_MAX));
// 	//INT_MIN
// 	check_isdigit(ft_isdigit(INT_MIN), isdigit(INT_MIN));
// }