/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:27 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:08:09 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c > 255 || c < 0))
		return (c);
	if (c >= 'A' && c <= 'Z')
		c = c + 32;
	return (c);
}

// #include <ctype.h>

// static void check_tolower(int i,int j)
// {
// 	printf("%d,%d",i,j);
// 	if(i == j)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	check_tolower(ft_tolower('a'), tolower('a'));
// 	check_tolower(ft_tolower('a' - 1), tolower('a' - 1));
// 	check_tolower(ft_tolower('a' + 1), tolower('a' + 1));
// 	check_tolower(ft_tolower('z'), tolower('z'));
// 	check_tolower(ft_tolower('z' - 1), tolower('z' - 1));
// 	check_tolower(ft_tolower('z' + 1), tolower('z' + 1));
// 	check_tolower(ft_tolower('A'), tolower('A'));
// 	check_tolower(ft_tolower('A' - 1), tolower('A' - 1));
// 	check_tolower(ft_tolower('A' + 1), tolower('A' + 1));
// 	check_tolower(ft_tolower('Z'), tolower('Z'));
// 	check_tolower(ft_tolower('Z' - 1), tolower('Z' - 1));
// 	check_tolower(ft_tolower('Z' + 1), tolower('Z' + 1));
// 	check_tolower(ft_tolower('a' + 256), tolower('a' + 256));
// 	check_tolower(ft_tolower('a' - 256), tolower('a' - 256));
// 	check_tolower(ft_tolower('a' + 1), tolower('a' + 1));
// 	check_tolower(ft_tolower('!'), tolower('!'));
// 	check_tolower(ft_tolower('{'), tolower('{'));
// 	check_tolower(ft_tolower('~'), tolower('~'));
// 	//zero
// 	check_tolower(ft_tolower(0), tolower(0));
// 	//INI_MAX
// 	check_tolower(ft_tolower(INT_MAX), tolower(INT_MAX));
// 	//INT_MIN
// 	check_tolower(ft_tolower(INT_MIN), tolower(INT_MIN));
// }