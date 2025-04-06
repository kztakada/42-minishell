/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:56:42 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 10:01:24 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <ctype.h>

// static int (*f)(int) = NULL;
// static void F(unsigned int i, char *s) { (void)i; *s = f(*s); };
// static int plus_one(int c) { return (c + 1); }

// static char buf[100] = {};

// static void tobuf(unsigned int i, char *str) {
//     static size_t   idx = 0;
//     (void)i;

//     buf[idx++] = *str;
// }

// static void check_striteri(char *actual,char *expected)
// {
// 	printf("%s,%s",actual,expected);
// 	if (strcmp(actual, expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int main(void)
// {
//     char str[] = "abcde";

//     f = toupper; ft_striteri(str, F);
//     check_striteri(str, "ABCDE");
//     f = plus_one; ft_striteri(str, F);
//     check_striteri(str, "BCDEF");
//     f = tolower; ft_striteri(str, F);
//     check_striteri(str, "bcdef");
//     f = plus_one; ft_striteri(str, F);
//     check_striteri(str, "cdefg");
//     f = toupper; ft_striteri(str, F);
//     check_striteri(str, "CDEFG");

//     bzero(buf, 100);
//     ft_striteri("hello", tobuf);
//     check_striteri(buf, "hello");
//     ft_striteri(" world", tobuf);
//     check_striteri(buf, "hello world");
//     ft_striteri(" 42!", tobuf);
//     check_striteri(buf, "hello world 42!");

// }
