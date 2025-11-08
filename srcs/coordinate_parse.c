#include "fdf.h"

void	safe_kill(int **tab1, char **tab2)
{
	int	i;

	i = 0;
	while (tab1[i] != NULL)
		free(tab1[i++]);
	free(tab1);
	i = 0;
	while (tab2[i] != NULL)
		free(tab2[i++]);
	free(tab2);
	exit(0);
}

void	free_coordinates(int **coordinates)
{
	int	i;

	i = 0;
	while (coordinates[i] != NULL)
		free(coordinates[i++]);
	free(coordinates);
}

void	free_doublestr(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	count_coordinates(char *str)
{
	int	i;
	int	n_coo;

	i = 0;
	n_coo = 0;
	while (str[i] && str[i] != '\n')
	{
		while (str[i] && str[i] != '\n' && str[i] == ' ')
			i++;
		if (ft_isnum(str[i]))
			n_coo++;
		while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
			i++;
	}
	return (n_coo);
}

int	*fill_coordinates(char *str, int *to_fill)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		to_fill[j] = 0;
		while (str[i] && str[i] != '\n' && str[i] == ' ')
			i++;
		while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
		{
			to_fill[j] += str[i] - '0';
			if (ft_isnum(str[i + 1]))
				to_fill[j] *= 10;
			i++;
		}
		j++;
	}
	return (to_fill);
}

int	**parse_coordinates(char **file, int nx, int ny)
{
	int	i;
	int	j;
	int	**coordinates;

	i = 0;
	j = 0;
	coordinates = malloc(sizeof(int *) * (ny + 1));
	if (coordinates == NULL)
		return (NULL);
	while (i < ny + 1)
		coordinates[i++] = NULL;
	i = 0;
	while (i < ny)
	{
		coordinates[i] = malloc(sizeof(int) * nx);
		if (coordinates[i] == NULL)
			safe_kill(coordinates, file);
		coordinates[i] = fill_coordinates(file[i], coordinates[i]);
		i++;
	}
	return (coordinates);
}

int	**get_coordinate(char *file_path, t_map *map)
{
	char	**file_content;

	file_content = get_file(file_path);
	map->ymax = count_lines(file_path);
	map->xmax = count_coordinates(file_content[0]);
	map->coordinates = parse_coordinates(file_content, map->xmax, map->ymax);
	free_doublestr(file_content);
	return (map->coordinates);
}
