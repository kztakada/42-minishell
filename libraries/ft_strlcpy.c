/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:16 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:17:37 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

// static void check_strlcpy(size_t actual,size_t expected)
// {
// 	printf("size_t:%zu,%zu",actual,expected);
// 	if (actual == expected)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// static void check_strlcpy_dst(char *actual,char *expected)
// {
// 	printf("dst:%s,%s",actual,expected);
// 	if (strcmp(actual,expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	char *dst1 = calloc(10, sizeof(char));
// 	char *dst2 = calloc(10, sizeof(char));
// 	char *src1 = calloc(10, sizeof(char));
// 	char *src2 = calloc(10, sizeof(char));
// 	memset(src1, 'z', 9);
// 	memset(src2, 'z', 9);
// 	check_strlcpy(ft_strlcpy(dst1, "", 10), strlcpy(dst2, "", 10));
// 	check_strlcpy_dst(dst1, dst2);
// 	check_strlcpy(ft_strlcpy(dst1, "hello", 10), strlcpy(dst2, "hello", 10));
// 	check_strlcpy_dst(dst1, dst2);
// 	check_strlcpy(ft_strlcpy(dst1, "world", 10), strlcpy(dst2, "world", 10));
// 	check_strlcpy_dst(dst1, dst2);
// 	check_strlcpy(ft_strlcpy(dst1, src1, 0), strlcpy(dst2, src2, 0));
// 	check_strlcpy_dst(dst1, dst2);
// 	check_strlcpy(ft_strlcpy(dst1, src1, 10), strlcpy(dst2, src2, 10));
// 	check_strlcpy(ft_strlcpy(NULL, "", 0), strlcpy(NULL, "", 0));
// 	free(dst1);
// 	free(dst2);
// 	free(src1);
// 	free(src2);
// }
