/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:06 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:13:21 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (str);
}

// static void	check_memset(char *s1, char *s2, int val, size_t size)
// {
// 	void	*actual = ft_memset(s1, val, size);
// 	void	*expected = memset(s2, val, size);
// 	if(memcmp(actual,expected,size) == 0)
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char	*s1, *s2;
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, 0, 0); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, 1, 0); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, 0, 1); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, 42, 0); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, 0, 42); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, 42, 42); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, INT_MAX, 42); free(s1); free(s2);
// 	s1 = calloc(100, 100); s2 = calloc(100, 100);
// 	check_memset(s1, s2, INT_MIN, 42); free(s1); free(s2);
// 	check_memset(NULL, NULL, 0, 0);
// 	// Very slow
// 	s1 = calloc(INT_MAX, 1); s2 = calloc(INT_MAX, 1);
// 	check_memset(s1, s2, 42, INT_MAX); free(s1); free(s2);
// }