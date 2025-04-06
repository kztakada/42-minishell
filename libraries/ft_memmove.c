/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:03 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:48:54 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	int		i;

	if (!dst && !src)
		return (NULL);
	s = (char *)src;
	d = (char *)dst;
	i = -1;
	if (d > s)
		while (len-- > 0)
			d[len] = s[len];
	else
		while (++i < (int)len)
			d[i] = s[i];
	return (dst);
}

// static void check_memmove(void *dst, void *src, size_t size)
// {
// 	void	*res_ft = memmove(dst, src, size);
// 	void	*expected = ft_memmove(dst, src, size);
// 	//nothing print cuz first index of s is　undisplayable characters
// 	printf("%s,%s->",(char *)res_ft,(char *)expected);
// 	if (memcmp(res_ft,expected,100) == 0)
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31mK[O]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char *src = malloc(100);
// 	for (int i = 0; i < 100; i++)
// 		src[i] = i;
// 	char *dst = malloc(100);
// 	check_memmove(dst, src, 0);
// 	check_memmove(dst, src, 10);
// 	check_memmove(dst, src, 100);
// 	// undefined: /* 3 forward overlap */ check_memmove(dst + 5, dst, 10);
// 	// undefined: /* 4 backward overlap*/ check_memmove(dst, dst + 3, 10);
// 	free(dst);
// 	free(src);
// 	return (0);
// }