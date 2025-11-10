/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:44:59 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/10 22:11:12 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int	skip_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n' && str[i] == ' ')
		i++;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
		i++;
	return (i);
}

void	fill_map(char *str, int *coordinates, unsigned long *colors, int nx)
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
		coordinates[j] = ft_atoi(&str[i]);
		i += skip_num(&str[i]);
		if (str[i] == ',')
		{
			i += 3;
			colors[j] = strhex_to_ulong(&str[i]);
			while (str[i] && ft_ishex(str[i]))
				i++;
		}
		j++;
	}
}

t_map	parse_file_content(t_map *map, char **file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < (map->ymax + 1))
	{
		map->colors[i] = NULL;
		map->coordinates[i++] = NULL;
	}
	i = 0;
	while (i < (map->ymax))
	{
		map->coordinates[i] = malloc(sizeof(int) * map->xmax);
		map->colors[i] = malloc(sizeof(unsigned long) * map->xmax);
		if (map->colors[i] == NULL)
			safe_kill(file, map->coordinates, map->colors);
		fill_map(file[i], map->coordinates[i], map->colors[i], map->xmax);
		i++;
	}
	return (*map);
}

t_map	init_map(char *file_path)
{
	t_map	map;
	char	**file_content;

	file_content = get_file(file_path);
	map.ymax = count_lines(file_path);
	map.xmax = count_coordinates(file_content[0]);
	map.coordinates = malloc(sizeof(int *) * (map.ymax + 1));
	map.colors = malloc(sizeof(unsigned long *) * (map.ymax + 1));
	if (!map.coordinates || !map.colors)
		safe_kill(file_content, map.coordinates, map.colors);
	map = parse_file_content(&map, file_content);
	return (map);
}
