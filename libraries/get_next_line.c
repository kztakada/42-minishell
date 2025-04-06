/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kharuya <haruya.0411.k@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 23:01:30 by kharuya           #+#    #+#             */
/*   Updated: 2025/03/12 22:51:58 by kharuya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*null_free(char **save)
{
	free (*save);
	*save = NULL;
	return (NULL);
}

static	char	*make_ans(char *save, ssize_t count_byte)
{
	char	*ans;
	int		i;

	ans = (char *)malloc(sizeof(char) * (count_byte + 1));
	if (!ans)
		return (NULL);
	i = -1;
	while (++i < count_byte)
		ans[i] = save[i];
	ans[count_byte] = '\0';
	return (ans);
}

static	char	*make_line(char **save, ssize_t count_byte)
{
	char	*ans;
	char	*tmp;

	if (count_byte == 0)
	{
		if (**save == '\0')
			return (null_free(save));
		ans = ft_strdup(*save);
		null_free (save);
		return (ans);
	}
	ans = make_ans(*save, count_byte);
	if (!ans)
		return (null_free(save));
	tmp = ft_substr(*save, count_byte, BUFFER_SIZE);
	if (!tmp)
		return (null_free(save));
	null_free (save);
	*save = tmp;
	return (ans);
}

static	char	*gnl_read(int fd, char *buffer, char **save)
{
	ssize_t	count_byte;
	char	*tmp;

	count_byte = 0;
	while (ft_strchr(*save, '\n') == NULL)
	{
		count_byte = read(fd, buffer, BUFFER_SIZE);
		if (count_byte == -1)
			return (null_free (save));
		else if (count_byte == 0)
			return (make_line(save, count_byte));
		buffer[count_byte] = '\0';
		tmp = ft_strjoin(*save, buffer);
		if (!tmp)
			return (null_free(save));
		null_free(save);
		*save = tmp;
	}
	return (make_line(save, ft_strchr(*save, '\n') - *save + 1));
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save)
	{
		save = ft_strdup("");
		if (!save)
			return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	result = gnl_read(fd, buffer, &save);
	free (buffer);
	return (result);
}
