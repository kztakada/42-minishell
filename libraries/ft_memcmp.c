/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:49:58 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:49:17 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;
	size_t			i;

	if (!s1 && !s2)
		return (0);
	s1_cpy = (unsigned char *)s1;
	s2_cpy = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_cpy[i] != s2_cpy[i])
			return (s1_cpy[i] - s2_cpy[i]);
		i++;
	}
	return (0);
}

// static void check_memcmp(int res_ft,int expected)
// {
// 	printf("(%d,%d->",res_ft,expected);
// 	if (res_ft == expected)
// 		printf("\x1b[32m[OK]\x1b[0m),");
// 	else
// 		printf("\x1b[31m[KO]\x1b[0m),");
// }

// int main()
// {
// 	int	len = 30;
// 	char *str = calloc(30, sizeof(char));
// 	char *cmp = calloc(30, sizeof(char));
// 	memcpy(str, "libft-test-tokyo", 16);
// 	memcpy(cmp, "libft-test-tokyo", 16);
// 	memcpy(str + 20, "acdfg", 5);
// 	memcpy(cmp + 20, "acdfg", 5);
// 	/* 1 ~ 31 */
// 	printf("Test1\n");
// 	for (int i = 0; i <= len; i++)
// 		check_memcmp(ft_memcmp(str, cmp, i), memcmp(str, cmp, i));
// 	printf("\nTest2\n");
// 	/* 32 ~ 93 */
// 	for (int i = 0; i <= len; i++)
// 	{
// 		cmp = strndup(str, i);
// 		check_memcmp(ft_memcmp(str, cmp, i), memcmp(str, cmp, i));
// 		check_memcmp(ft_memcmp(str, cmp, len), memcmp(str, cmp, len));
// 		free(cmp);
// 	}
// 	free(str);
// 	free(cmp);
// }