/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:12:08 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/20 04:47:44 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

void	error_handle(int argc)
{
	if (argc > 2)
		write(1, "Error : Too many files\n", 23);
	else if (argc < 2)
		write(1, "Error : No file turned in\n", 26);
	else
		perror(strerror(errno));
	exit(0);
}

int	count_lines(char *file_path)
{
	int		file;
	int		lines;
	char	buffer;

	lines = 0;
	file = open(file_path, O_RDONLY);
	while (read(file, &buffer, 1))
	{
		if (buffer == '\n')
			lines++;
	}
	close(file);
	return (lines);
}

char	**get_file(char *file_path)
{
	int		i;
	int		file;
	char	**parsed;

	i = 0;
	file = open(file_path, O_RDONLY);
	if (file < 0)
		kill_error(file_path);
	parsed = malloc(sizeof(char *) * (count_lines(file_path) + 1));
	if (parsed == NULL)
		return (NULL);
	parsed[count_lines(file_path)] = NULL;
	parsed[0] = get_next_line(file);
	while (parsed[i++] != NULL)
		parsed[i] = get_next_line(file);
	close(file);
	return (parsed);
}
