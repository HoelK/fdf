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
		if (str[i] == '-')
			i++;
		if (ft_isnum(str[i]))
			n_coo++;
		while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
			i++;
		if (str[i] == ',')
			i += 3;
		while (str[i] && str[i] != '\n' && ft_ishex(str[i]))
			i++;
	}
	return (n_coo);
}

int	*fill_coordinates(char *str, int *coordinates, unsigned long *colors, int nx)
{
	int	i;
	int	j;
	int	neg;

	i = 0;
	j = 0;
	neg = 0;
	while (str[i] && str[i] != '\n' && j < nx)
	{
		colors[j] = 16777215;
		coordinates[j] = 0;
		while (str[i] && str[i] != '\n' && str[i] == ' ')
			i++;
		if (str[i] == '-')
		{
			neg = 1;
			i++;
		}
		while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
		{
			coordinates[j] += str[i] - '0';
			if (ft_isnum(str[i + 1]))
				coordinates[j] *= 10;
			i++;
		}
		if (neg)
			coordinates[j] = -coordinates[j];
		neg = 0;
		if (str[i] == ',')
		{
			i += 3;
			colors[j] = strhex_to_ulong(&str[i]);
			while (str[i] && str[i] != '\n' && ft_ishex(str[i]))
				i++;
		}
		j++;
	}
	return (coordinates);
}

int	**parse_coordinates(char **file, unsigned long ***colors, int nx, int ny)
{
	int	i;
	int	j;
	int	**coordinates;

	i = 0;
	j = 0;
	coordinates = malloc(sizeof(int *) * (ny + 1));
	if (coordinates == NULL)
		return (NULL);
	*colors = malloc(sizeof(unsigned long *) * (ny + 1));
	if (*colors == NULL)
		return (free(coordinates), NULL);
	while (i < ny + 1)
	{
		(*colors)[i] = NULL;
		coordinates[i++] = NULL;
	}
	i = 0;
	while (i < ny)
	{
		coordinates[i] = malloc(sizeof(int) * nx);
		if (coordinates[i] == NULL)
			safe_kill(coordinates, file);
		(*colors)[i] = malloc(sizeof(unsigned long) * nx);
		if ((*colors)[i] == NULL)
			safe_kill(coordinates, file);
		coordinates[i] = fill_coordinates(file[i], coordinates[i], (*colors)[i], nx);
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
	map->coordinates = parse_coordinates(file_content, &map->colors, map->xmax, map->ymax);
	free_doublestr(file_content);
	return (map->coordinates);
}
