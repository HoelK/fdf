#include "fdf.h"

void	free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

int	count_lines(char *file_path)
{
	int	file;
	int	lines;
	char	buffer;

	lines = 0;
	file = open(file_path, O_RDONLY);
	while(read(file, &buffer, 1))
	{
		if (buffer == '\n')
			lines++;
	}
	close(file);
	return (lines);
}

void	error_handle(int argc)
{
	if (argc > 2)
		printf("Error : Too many files");
	else if (argc < 2)
		printf("Error : No file turned in");
	else
		perror(strerror(errno));
	exit(0);
}

char	**get_file(char *file_path)
{
	int	i;
	int	file;
	char	**parsed;

	i = 0;
	file = open(file_path, O_RDONLY);
	if (file < 0)
		error_handle(1);
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
