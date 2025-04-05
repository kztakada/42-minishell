/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:49:55 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:49:24 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ans;

	s_ans = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*s_ans == (unsigned char)c)
			return ((void *)s_ans);
		s_ans++;
	}
	return (NULL);
}

// static void check_memchr(const char *res_ft,const char *expected)
// {
// 	printf("res_ft=%s expected=%s",res_ft,expected);
// 	if(!res_ft && !expected)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else if(*res_ft == '\0' && *expected == '\0')
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else if (strcmp(res_ft, expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main()
// {
// 	// s = "libft-test-tokyo\0\0\0acdfg\0\0\0\0\0"
// 	char *s = calloc(30, sizeof(char));
// 	memcpy(s, "libft-test-tokyo", 17);
// 	memcpy(s + 20, "acdfg", 5);
// 	check_memchr(ft_memchr(s, 'l', 30), memchr(s, 'l', 30));
// 	check_memchr(ft_memchr(s, 'i', 30), memchr(s, 'i', 30));
// 	check_memchr(ft_memchr(s, 'b', 30), memchr(s, 'b', 30));
// 	check_memchr(ft_memchr(s, 'f', 30), memchr(s, 'f', 30));
// 	check_memchr(ft_memchr(s, 't', 30), memchr(s, 't', 30));
// 	check_memchr(ft_memchr(s, '-', 30), memchr(s, '-', 30));
// 	check_memchr(ft_memchr(s, 't', 30), memchr(s, 't', 30));
// 	check_memchr(ft_memchr(s, 'e', 30), memchr(s, 'e', 30));
// 	check_memchr(ft_memchr(s, 's', 30), memchr(s, 's', 30));
// 	check_memchr(ft_memchr(s, 't', 30), memchr(s, 't', 30));
// 	check_memchr(ft_memchr(s, '-', 30), memchr(s, '-', 30));
// 	check_memchr(ft_memchr(s, 't', 30), memchr(s, 't', 30));
// 	check_memchr(ft_memchr(s, 'o', 30), memchr(s, 'o', 30));
// 	check_memchr(ft_memchr(s, 'k', 30), memchr(s, 'k', 30));
// 	check_memchr(ft_memchr(s, 'y', 30), memchr(s, 'y', 30));
// 	check_memchr(ft_memchr(s, 'o', 30), memchr(s, 'o', 30));
// 	check_memchr(ft_memchr(s, '\0', 30), memchr(s, '\0', 30));

// 	// char overflow
// 	check_memchr(ft_memchr(s, 'l' + 256, 30), memchr(s, 'l' + 256, 30));
// 	check_memchr(ft_memchr(s, 'i' + 256, 30), memchr(s, 'i' + 256, 30));
// 	check_memchr(ft_memchr(s, 'l' - 256, 30), memchr(s, 'l' - 256, 30));
// 	check_memchr(ft_memchr(s, 'i' - 256, 30), memchr(s, 'i' - 256, 30));

// 	// unseen characters
// 	check_memchr(ft_memchr(s, 'z', 30), memchr(s, 'z', 30));
// 	check_memchr(ft_memchr(s, '~', 30), memchr(s, '~', 30));

// 	// characters after' \0'
// 	check_memchr(ft_memchr(s, 'a', 30), memchr(s, 'a', 30));
// 	check_memchr(ft_memchr(s, 'c', 30), memchr(s, 'c', 30));
// 	check_memchr(ft_memchr(s, 'd', 30), memchr(s, 'd', 30));
// 	check_memchr(ft_memchr(s, 'f', 30), memchr(s, 'f', 30));
// 	check_memchr(ft_memchr(s, 'g', 30), memchr(s, 'g', 30));
// 	free(s);
// }