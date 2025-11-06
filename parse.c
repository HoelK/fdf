#include <stdio.h>
#include "get_next_line.h"

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

char	**get_file(char *file_path)
{
	int	i;
	int	file;
	char	**parsed;

	i = 0;
	file = open(file_path, O_RDONLY);
	parsed = malloc(sizeof(char *) * count_lines(file_path) + 1);
	if (parsed == NULL)
		return (NULL);
	parsed[count_lines(file_path)] = NULL;
	parsed[0] = get_next_line(file);
	while (parsed[i++] != NULL)
		parsed[i] = get_next_line(file);
	close(file);
	return (parsed);
}

void print_file(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		printf("%s\n", strs[i++]);
}

int	main(void)
{
	char	**file;
	file = get_file("./test_maps/42.fdf");
	print_file(file);
	free_all(file);
}
