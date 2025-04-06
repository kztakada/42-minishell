/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:11 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 10:04:11 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ans;
	char	*ans_cpy;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2);
		ans = (char *)malloc(sizeof(char) * (len + 1));
		if (ans == NULL)
			return (NULL);
		ans_cpy = ans;
		while (*s1)
			*(ans_cpy++) = *(s1++);
		while (*s2)
			*(ans_cpy++) = *(s2++);
		*ans_cpy = '\0';
		return (ans);
	}
	return (NULL);
}

// static void check_strjoin(char *actual,char *expected)
// {
// 	printf("%s,%s",actual,expected);
// 	if (strcmp(actual, expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	check_strjoin(ft_strjoin("hello", "world"), "helloworld");
// 	check_strjoin(ft_strjoin("", "world"), "world");
// 	check_strjoin(ft_strjoin("hello", ""), "hello");
// 	check_strjoin(ft_strjoin("", ""), "");
// }