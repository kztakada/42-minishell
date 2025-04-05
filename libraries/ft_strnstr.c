/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:31:25 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:22:44 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	v;
	size_t	i;

	if (!needle[0] || (!haystack && !len))
		return ((char *)haystack);
	v = 0;
	while (haystack[v] && v < len)
	{
		i = 0;
		if (haystack[v] == needle[i])
		{
			while (needle[i] && (v + i < len))
			{
				if (needle[i] != haystack[i + v])
					break ;
				else if (needle [i + 1] == '\0')
					return ((char *)haystack + v);
				i++;
			}
		}
		v++;
	}
	return (NULL);
}

// static void check_nstr(char *actual,char *expected)
// {
// 	if(!actual && !expected)
// 	{
// 		printf("%s,%s",actual,expected);
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 		return ;
// 	}
// 	printf("%s,%s",actual,expected);
// 	if(strcmp(actual,expected) == 0)
//         printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char *str = "libft-test-tokyo";
// 	int	len = ft_strlen(str);
// 	for (int i = 0; i < len; i++)
// 	{
// 		check_nstr(ft_strnstr(str, "", i), strnstr(str, "", i));
// 		check_nstr(ft_strnstr(str, "libft", i), strnstr(str, "libft", i));
// 		check_nstr(ft_strnstr(str, "test", i), strnstr(str, "test", i));
// 		check_nstr(ft_strnstr(str, "tokyo", i), strnstr(str, "tokyo", i));
// 		check_nstr(ft_strnstr(str, "libft~", i), strnstr(str, "libft~", i));
// 		check_nstr(ft_strnstr(str, "z", i), strnstr(str, "z", i));
// 	}
// }