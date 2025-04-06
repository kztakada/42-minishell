/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:25 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:17:58 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s1, int c)
{
	char	*s;
	size_t	s_len;

	s = (char *)s1;
	s_len = ft_strlen(s) + 1;
	while (s_len > 0)
	{
		if (s[s_len - 1] == (char)c)
			return (s + s_len - 1);
		s_len--;
	}
	return (NULL);
}

// static void check_strrchr(char *actual,char *expected)
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
// 	char *s = "libft-test-tokyo";
// 	check_strrchr(ft_strrchr(s, 'l'), strrchr(s, 'l'));
// 	check_strrchr(ft_strrchr(s, 'i'), strrchr(s, 'i'));
// 	check_strrchr(ft_strrchr(s, 'b'), strrchr(s, 'b'));
// 	check_strrchr(ft_strrchr(s, 'f'), strrchr(s, 'f'));
// 	check_strrchr(ft_strrchr(s, 't'), strrchr(s, 't'));
// 	check_strrchr(ft_strrchr(s, '-'), strrchr(s, '-'));
// 	check_strrchr(ft_strrchr(s, 't'), strrchr(s, 't'));
// 	check_strrchr(ft_strrchr(s, 'e'), strrchr(s, 'e'));
// 	check_strrchr(ft_strrchr(s, 's'), strrchr(s, 's'));
// 	check_strrchr(ft_strrchr(s, 't'), strrchr(s, 't'));
// 	check_strrchr(ft_strrchr(s, '-'), strrchr(s, '-'));
// 	check_strrchr(ft_strrchr(s, 't'), strrchr(s, 't'));
// 	check_strrchr(ft_strrchr(s, 'o'), strrchr(s, 'o'));
// 	check_strrchr(ft_strrchr(s, 'k'), strrchr(s, 'k'));
// 	check_strrchr(ft_strrchr(s, 'y'), strrchr(s, 'y'));
// 	check_strrchr(ft_strrchr(s, 'o'), strrchr(s, 'o'));
// 	check_strrchr(ft_strrchr(s, '\0'), strrchr(s, '\0'));
// 	check_strrchr(ft_strrchr(s, 'l' + 256), strrchr(s, 'l' + 256));
// 	check_strrchr(ft_strrchr(s, 'i' + 256), strrchr(s, 'i' + 256));
// 	check_strrchr(ft_strrchr(s, 'l' - 256), strrchr(s, 'l' - 256));
// 	check_strrchr(ft_strrchr(s, 'i' - 256), strrchr(s, 'i' - 256));
// 	check_strrchr(ft_strrchr(s, 'z'), strrchr(s, 'z'));
// 	check_strrchr(ft_strrchr(s, '~'), strrchr(s, '~'));
// 	return (0);
// }