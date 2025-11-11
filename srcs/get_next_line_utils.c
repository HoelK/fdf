/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 19:32:30 by hkeromne          #+#    #+#             */
/*   Updated: 2025/10/29 15:39:45 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*join_and_free(char *s1_tofree, char *buffer)
{
	char	*result;

	result = ft_strjoin(s1_tofree, buffer);
	free(s1_tofree);
	return (result);
}

char	*kill_func(char *buffer, char **rest, int error)
{
	char	*line;

	line = NULL;
	if (error == 0 && *rest && **rest)
		line = ft_strjoin(*rest, buffer);
	if (buffer)
		free(buffer);
	if (*rest)
	{
		free(*rest);
		*rest = NULL;
	}
	return (line);
}

int	ft_lento(char *s, char c)
{
	int	len;

	if (!s || (!*s && *s == c))
		return (0);
	if (!*s && *s != c)
		return (-1);
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	if (s[len] == c)
		return (len);
	return (-1);
}

char	*ft_strdup(char	*s)
{
	int		i;
	char	*result;

	i = -1;
	result = malloc(sizeof(char) * ft_lento(s, '\0') + 1);
	while (s[++i])
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}

char	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	char	*result;

	i = 0;
	result = malloc(n * size);
	if (result == NULL)
		return (NULL);
	while (i < n * size)
		result[i++] = 0;
	return (result);
}
