/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:49:38 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:21:01 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*res;
	size_t	i;

	res = (char *)s;
	i = 0;
	while (i < n)
		res[i++] = 0;
}

// static void	check_bzero(char *s1, char *s2, size_t size)
// {
// 	memset(s1, 'A', size);
// 	memset(s2, 'B', size);
// 	ft_bzero(s1, size);
// 	bzero(s2, size);
// 	void	*actual = s1;
// 	void	*expected = s2;
// 	if(memcmp(actual,expected,size) == 0)
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31mK[O]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char	*s1, *s2;
// 	s1 = malloc(100); s2 = malloc(100); check_bzero(s1, s2, 0);
// 	free(s1); free(s2);
// 	s1 = malloc(100); s2 = malloc(100); check_bzero(s1, s2, 1);
// 	free(s1); free(s2);
// 	s1 = malloc(100); s2 = malloc(100); check_bzero(s1, s2, 42);
// 	free(s1); free(s2);
// 	s1 = malloc(100); s2 = malloc(100); check_bzero(s1, s2, 100);
// 	free(s1); free(s2);
// 	// No seguemtation fault
// 	// /* 5 */ ft_bzero(NULL, 0); bzero(NULL, 0);
// 	// Segmentation Fault
// 	// /* 5 */ ft_bzero(NULL, 1); bzero(NULL, 1);
// }