/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:50:11 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:47:51 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ans;
	size_t	s1_len;
	int		i;

	s1_len = ft_strlen(s);
	ans = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!ans)
		return (NULL);
	i = -1;
	while (s[++i])
		ans[i] = s[i];
	ans[i] = '\0';
	return (ans);
}

// static void	check_strdup(char *str)
// {
// 	void	*actual = ft_strdup(str);
// 	void	*expected = strdup(str);
// 	printf("%s,%s\n",(char *)actual,(char *)expected);
// 	if(strcmp(actual,expected) == 0)
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
//         printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	check_strdup("");
// 	check_strdup("hello");
// 	check_strdup("hello world");
// 	char *str = malloc(1000);
// 	str = memset(str, 'A', 999);
// 	str[999] = '\0';
// 	check_strdup(str);

// 	// Segmentation Fault
// 	// /* 1,2 */ check_strdup(NULL);
// 	free(str);
// }