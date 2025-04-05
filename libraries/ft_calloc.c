/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <kharuya@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:49:43 by kharuya           #+#    #+#             */
/*   Updated: 2024/05/14 09:24:34 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ans;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ans = (void *)malloc(count * size);
	if (!ans)
		return (ans);
	ft_bzero(ans, size * count);
	return (ans);
}

// #include <malloc/malloc.h>

// static void	check_calloc(size_t cnt, size_t size)
// {
// 	void	*actual = ft_calloc(cnt, size);
// 	void	*expected = calloc(cnt, size);
// 	//mallc_check
// 	//this part will use if calloc do NULL guard
// 	if(expected == NULL || actual == NULL)
// 	{
// 		if (expected != actual)
// 			printf("\x1b[31m[KO]\x1b[0m\n");
// 		else
// 			printf("\x1b[32m[OK]\x1b[0m\n");
// 	}
// 	//this part will use if calloc make malloc and success
// 	if (malloc_size(actual) != malloc_size(expected))
// 		printf("\x1b[31m[KO]\x1b[0m\n");
// 	else
// 		printf("\x1b[32m[OK]\x1b[0m\n");
// 	free(actual);
// 	free(expected);
// }

// int	main(void)
// {
// 	check_calloc(0, 0);
// 	check_calloc(1, 0);
// 	check_calloc(0, 1);
// 	check_calloc(1, 1);
// 	check_calloc(42, 1);
// 	check_calloc(1, 42);
// 	check_calloc(42, 42);
// 	//overflow
// 	check_calloc((size_t)SIZE_MAX / 10 + (size_t)1, 10);
// 	// //too big 1
// 	check_calloc(LONG_MAX, 1);
// 	// //too big 2
// 	check_calloc(ULONG_MAX, 1);
// 	// //too big 3
// 	check_calloc(SIZE_MAX, 1);
// 	return (0);
// }