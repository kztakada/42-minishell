/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:18 by kharuya           #+#    #+#             */
/*   Updated: 2025/03/12 22:57:49 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
// static void check_strlen(size_t actual,size_t expected)
// {
// 	printf("%zu,%zu",actual,expected);
// 	if(actual == expected)
//         printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	check_strlen(ft_strlen(""), strlen(""));
// 	check_strlen(ft_strlen("hello"), strlen("hello"));
// 	check_strlen(ft_strlen("hello world"), strlen("hello world"));
// }