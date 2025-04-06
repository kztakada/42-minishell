/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:01 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:11:53 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_res;
	const char	*src_res;
	size_t		i;

	if (!dst && !src)
		return (NULL);
	dst_res = (char *)dst;
	src_res = (const char *)src;
	i = 0;
	while (i < n)
	{
		dst_res[i] = src_res[i];
		i++;
	}
	return (dst);
}

// static void check_memcpy(void *dst, void *src, size_t size)
// {
// 	void	*res_ft = memcpy(dst, src, size);
// 	void	*expected = ft_memcpy(dst, src, size);
// 	//nothing print cuz first index of s is　undisplayable characters
// 	printf("%s,%s->",(char *)res_ft,(char *)expected);
// 	if (memcmp(res_ft,expected,100) == 0)
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char *src = malloc(100);
// 	for (int i = 0; i < 100; i++)
// 		src[i] = i;
// 	char *dst = malloc(100);
// 	check_memcpy(dst, src, 0);
// 	check_memcpy(dst, src, 10);
// 	check_memcpy(dst, src, 100);
// 	// undefined: /* 3 forward overlap */ check_memcpy(dst + 5, dst, 10);
// 	// undefined: /* 4 backward overlap*/ check_memcpy(dst, dst + 3, 10);
// 	free(dst);
// 	free(src);
// 	return (0);
// }