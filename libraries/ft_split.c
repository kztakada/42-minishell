/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:55:50 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:48:26 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_row_count(char const *s, char c)
{
	int	row;

	row = 0;
	while (*s)
	{
		if (*s != c)
		{
			row++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (row);
}

static char	*ft_col_count(char const *s, char c, int j)
{
	int		start;
	int		col;
	char	*res;
	char	*res_cpy;

	start = j;
	col = 0;
	while (s[j] && s[j++] != c)
		col++;
	res = (char *)malloc(sizeof(char) * (col + 1));
	if (res == NULL)
		return (res);
	res_cpy = res;
	while (col-- > 0)
		*(res_cpy++) = s[start++];
	*res_cpy = '\0';
	return (res);
}

static char	**ft_free(char **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		row;
	char	**ans;

	if (!s)
		return (0);
	row = ft_row_count(s, c);
	ans = (char **)malloc(sizeof(char *) * (row + 1));
	if (!ans)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < row)
	{
		while (s[j] && s[j] == c)
			j++;
		ans[i] = ft_col_count(s, c, j);
		if (!ans[i])
			return (ft_free(ans, i));
		while (s[j] && s[j] != c)
			j++;
	}
	ans[i] = NULL;
	return (ans);
}

// static void	check_split(char **actual, char **expected)
// {
// 	int i = -1;
// 	// Check the non NULL elements
// 	while (expected[++i])
// 	{
// 		printf("%s,%s\n",actual[i],expected[i]);
// 		if (strcmp(actual[i],expected[i]) != 0)
// 		{
// 			printf("\x1b[31m->[KO]\x1b[0m\n");
// 			return ;
// 		}
// 	}
// 	printf("%s,%s\n",actual[i],expected[i]);
// 	if (!actual[i] && !expected[i])
// 		printf("\x1b[32m->[OK]\x1b[0m\n");
// 	else
// 		printf("\x1b[31m->[KO]\x1b[0m\n");
// }

// int	main(void)
// {
// 	char *expected[] = {"hello","world","42","tokyo", NULL};
// 	check_split(ft_split("hello,world,42,tokyo", ','), expected);
// 	check_split(ft_split("hello world 42 tokyo", ' '), expected);
// 	check_split(ft_split(",,,hello,,,world,,,42,,,tokyo,,,,", ','), expected);

// 	char *expected2[] = {"hello,world,42,tokyo", NULL};
// 	check_split(ft_split("hello,world,42,tokyo", ' '), expected2);
// 	check_split(ft_split("hello,world,42,tokyo", '{'), expected2);

// 	char *expected3[] = {NULL};
// 	check_split(ft_split("", ','), expected3);

// 	// Segmentation Fault
// 	// /* 21 */ check_split(ft_split(NULL, ','), expected3);
// }