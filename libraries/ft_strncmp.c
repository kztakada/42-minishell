/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:21 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 10:39:46 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0 || (!s1 && !s2))
		return (0);
	while ((s1[i] || s2[i]) && n-- > 0)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// static void check_strncmp(int actual,int expected)
// {
// 	printf("%d,%d",actual,expected);
// 	if(actual == expected)
//         printf("\x1b[32m->[OK]\x1b[0m\n");
//     else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }
// int	main(void)
// {
// 	char *str = "libft-test-tokyo";
// 	char *cmp = "libft-test-tokyo";
// 	int	len = strlen(str);
// 	/* 1 ~ 17 */
// 	for (int i = 0; i <= len; i++)
// 		check_strncmp(ft_strncmp(str, cmp, i), strncmp(str, cmp, i));
// 	/* 18 ~ 51 */
// 	for (int i = 0; i <= len; i++)
// 	{
// 		cmp = strndup(str, i);
// 		check_strncmp(ft_strncmp(str, cmp, i), strncmp(str, cmp, i));
// 		check_strncmp(ft_strncmp(str, cmp, len), strncmp(str, cmp, len));
// 		free(cmp);
// 	}
// }