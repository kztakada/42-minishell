/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:28 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 11:23:33 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_detect_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_ans_len(char const *s1, char const *set)
{
	int		s1_index;
	size_t	ans_len;

	s1_index = ft_strlen(s1) - 1;
	while (s1_index >= 0)
	{
		if (!ft_detect_set(s1[s1_index], set))
			break ;
		s1_index--;
	}
	ans_len = (size_t)s1_index + 1;
	return (ans_len);
}

static char	*ft_make_ans(char *ans, char const *s1, int ans_len)
{
	int	i;

	i = 0;
	while (ans_len--)
	{
		ans[i] = s1[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	ans_len;
	char	*ans;

	if (!s1 || !set)
		return (NULL);
	while (ft_detect_set(*s1, set))
		s1++;
	ans_len = ft_ans_len(s1, set);
	ans = (char *)malloc(sizeof(char) * (ans_len + 1));
	if (!ans)
		return (NULL);
	return (ft_make_ans(ans, s1, ans_len));
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
// 	free(actual);
// }

// int	main(void)
// {
// 	check_nstr(ft_strtrim("hello world", "world"), "hello ");
// 	check_nstr(ft_strtrim("hello world", "hello"), " world");
// 	check_nstr(ft_strtrim("hello world", ""), "hello world");
// 	check_nstr(ft_strtrim("", ""), "");
// 	check_nstr(ft_strtrim("    hello world     ", " "), "hello world");
// 	check_nstr(ft_strtrim("hello world", "abcdefghijklmnopqrstuvwxyz"), " ");
// }