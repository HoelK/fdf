/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:13:54 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/01 20:11:42 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = (ft_lento(s1, '\0') + ft_lento(s2, '\0') + 1);
	result = ft_calloc(sizeof(char), j);
	if (result == NULL)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
	}
	if (s2 != NULL)
	{
		j = 0;
		while (s2[j])
			result[i++] = s2[j++];
	}
	result[i] = '\0';
	return (result);
}

char	*fill_rest(char *buffer, char *rest)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	j = ft_lento(buffer, '\n') + 1;
	if (!j)
		return (free(rest), NULL);
	len = ft_lento(&buffer[j], '\0');
	while (i < len)
		rest[i++] = buffer[j++];
	while (i < BUFFER_SIZE)
	{
		rest[i] = 0;
		i++;
	}
	return (rest);
}

//we assume buffer is malloced and needs to be free
char	*extract_line(char *full_line)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	i = -1;
	j = 0;
	len = ft_lento(full_line, '\n') + 1;
	if (!len)
		len = ft_lento(full_line, '\0');
	result = ft_calloc(sizeof(char), len + 1);
	if (!result)
		return (NULL);
	while (++i < len)
		result[i] = full_line[i];
	result[i] = 0;
	while (full_line[i])
		full_line[j++] = full_line[i++];
	while (full_line[j])
		full_line[j++] = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*rest;
	int			i;

	if (fd < 0 || fd > FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!rest || (!(ft_lento(buffer, '\n') + 1)
			&& !(ft_lento(rest, '\n') + 1)))
	{
		i = 0;
		while (i < BUFFER_SIZE)
			buffer[i++] = 0;
		i = read(fd, buffer, BUFFER_SIZE);
		if (i <= 0)
			return (kill_func(buffer, &rest, i));
		rest = join_and_free(rest, buffer);
		if (!rest)
			return (free(buffer), NULL);
	}
	return (free(buffer), extract_line(rest));
}
