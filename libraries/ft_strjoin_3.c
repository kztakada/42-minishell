/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katakada <katakada@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 03:24:28 by kharuya           #+#    #+#             */
/*   Updated: 2025/06/06 16:06:47 by katakada         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_3(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*ans;
	char	*ans_cpy;

	if (s1 && s2)
	{
		len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
		ans = (char *)malloc(sizeof(char) * (len + 1));
		if (ans == NULL)
			return (NULL);
		ans_cpy = ans;
		while (*s1)
			*(ans_cpy++) = *(s1++);
		while (*s2)
			*(ans_cpy++) = *(s2++);
		if (s3)
		{
			while (*s3)
				*(ans_cpy++) = *(s3++);
		}
		*ans_cpy = '\0';
		return (ans);
	}
	return (NULL);
}
