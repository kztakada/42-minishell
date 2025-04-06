/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:14 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:17:00 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = ft_strlen(dst);
	if (dstsize > dst_len)
	{
		while (src[i] && j < dstsize - 1)
			dst[j++] = src[i++];
		dst[j] = '\0';
		return (dst_len + src_len);
	}
	else
		return (dstsize + src_len);
}

// static void check_strlcat(size_t actual,size_t expected)
// {
// 	printf("size_t:%zu,%zu",actual,expected);
// 	if (actual == expected)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// static void check_strlcat_dst(char *actual,char *expected)
// {
// 	printf("dst:%s,%s",actual,expected);
// 	if (strcmp(actual,expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char *dst1 = calloc(100, sizeof(char));
// 	char *dst2 = calloc(100, sizeof(char));
// 	check_strlcat(ft_strlcat(dst1, "", 100), strlcat(dst2, "", 100));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, "hello", 100), strlcat(dst2, "hello", 100));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, "world", 100), strlcat(dst2, "world", 100));
// 	check_strlcat_dst(dst1, dst2);
// 	char *src1 = calloc(100, sizeof(char));
// 	char *src2 = calloc(100, sizeof(char));
// 	for (int i = 0; i < 99; i++)
// 	{
// 		src1[i] = i + 1;
// 		src2[i] = i + 1;
// 	}
// 	check_strlcat(ft_strlcat(dst1, src1, 0), strlcat(dst2, src2, 0));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, src1, 10), strlcat(dst2, src2, 10));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, src1, 50), strlcat(dst2, src2, 50));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, src1, 100), strlcat(dst2, src2, 100));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, src1, 10), strlcat(dst2, src2, 10));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(dst1, src1, 100), strlcat(dst2, src2, 100));
// 	check_strlcat_dst(dst1, dst2);
// 	check_strlcat(ft_strlcat(NULL, src1, 0), strlcat(NULL, src2, 0));
// 	free(dst1);
// 	free(dst2);
// 	free(src1);
// 	free(src2);
// }