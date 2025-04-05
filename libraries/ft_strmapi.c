/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:56:37 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/24 14:39:21 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ans;
	int		count_char;
	int		i;

	if (!s)
		return (NULL);
	count_char = ft_strlen(s);
	ans = (char *)malloc(sizeof(char) * (count_char + 1));
	if (!ans)
		return (NULL);
	i = -1;
	while (s[++i])
		ans[i] = f(i, s[i]);
	ans[i] = '\0';
	return (ans);
}

// #include <ctype.h>

// static int (*f)(int) = NULL;
// static char F(unsigned int i, char c) { (void)i; return (f(c)); };
// static int plus_one(int c) { return (c + 1); }

// static void check_strmapi(char *actual,char *expected)
// {
// 	printf("%s,%s",actual,expected);
// 	if(strcmp(actual,expected) == 0)
//         printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// 	free(actual);
// }

// int main(void)
// {
//     f = toupper;
//     check_strmapi(ft_strmapi("abcde", F), "ABCDE");
//     check_strmapi(ft_strmapi("Hello World!", F), "HELLO WORLD!");
//     check_strmapi(ft_strmapi("12345", F), "12345");
//     f = tolower;
//     check_strmapi(ft_strmapi("ABCDE", F), "abcde");
//     check_strmapi(ft_strmapi("Hello World!", F), "hello world!");
//     check_strmapi(ft_strmapi("12345", F), "12345");
//     f = plus_one;
//     check_strmapi(ft_strmapi("ABCDE", F), "BCDEF");
//     check_strmapi(ft_strmapi("Hello World!", F), "Ifmmp!Xpsme\"");
//     check_strmapi(ft_strmapi("12345", F), "23456");
// }