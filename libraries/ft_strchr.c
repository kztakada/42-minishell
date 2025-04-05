/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:09 by kharuya           #+#    #+#             */
/*   Updated: 2025/03/12 22:58:11 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	char	*s;

	if (!src)
		return (NULL);
	s = (char *)src;
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == (char)c)
		return (s);
	return (NULL);
}

// static void	check_strchr(char *actual,char *expected)
// {
// 	printf("%s,%s->",actual,expected);
// 	if (!actual && !expected)
// 	{
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 		return ;
// 	}
// 	if (strcmp(actual, expected) == 0)
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char *s = "libft-test-tokyo";
// 	check_strchr(ft_strchr(s, 'l'), strchr(s, 'l'));
// 	check_strchr(ft_strchr(s, 'i'), strchr(s, 'i'));
// 	check_strchr(ft_strchr(s, 'b'), strchr(s, 'b'));
// 	check_strchr(ft_strchr(s, 'f'), strchr(s, 'f'));
// 	check_strchr(ft_strchr(s, 't'), strchr(s, 't'));
// 	check_strchr(ft_strchr(s, '-'), strchr(s, '-'));
// 	check_strchr(ft_strchr(s, 't'), strchr(s, 't'));
// 	check_strchr(ft_strchr(s, 'e'), strchr(s, 'e'));
// 	check_strchr(ft_strchr(s, 's'), strchr(s, 's'));
// 	check_strchr(ft_strchr(s, 't'), strchr(s, 't'));
// 	check_strchr(ft_strchr(s, '-'), strchr(s, '-'));
// 	check_strchr(ft_strchr(s, 't'), strchr(s, 't'));
// 	check_strchr(ft_strchr(s, 'o'), strchr(s, 'o'));
// 	check_strchr(ft_strchr(s, 'k'), strchr(s, 'k'));
// 	check_strchr(ft_strchr(s, 'y'), strchr(s, 'y'));
// 	check_strchr(ft_strchr(s, 'o'), strchr(s, 'o'));
// 	check_strchr(ft_strchr(s, '\0'), strchr(s, '\0'));
// 	check_strchr(ft_strchr(s, 'l' + 256), strchr(s, 'l' + 256));
// 	check_strchr(ft_strchr(s, 'i' + 256), strchr(s, 'i' + 256));
// 	check_strchr(ft_strchr(s, 'l' - 256), strchr(s, 'l' - 256));
// 	check_strchr(ft_strchr(s, 'i' - 256), strchr(s, 'i' - 256));
// 	check_strchr(ft_strchr(s, 'z'), strchr(s, 'z'));
// 	check_strchr(ft_strchr(s, '~'), strchr(s, '~'));
// 	return (0);
// }