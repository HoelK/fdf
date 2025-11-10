/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:40:37 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/10 22:31:27 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_map(t_display *display, t_map *map)
{
	//display_x(display, map);
	//display_y(display, map);
	display_all(display, map);
}

void	display_y(t_display *display, t_map *map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < map->ymax)
	{
		while ((x + 1) < map->xmax)
		{
			map->vertex1 = get_vertex(x, y, &map->vertex1, map);
			map->vertex2 = get_vertex(x + 1, y, &map->vertex2, map);
			display_line(display, &map->vertex1, &map->vertex2);
			x++;
		}
		x = 0;
		y++;
	}
}

void	display_x(t_display *display, t_map *map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (x < map->xmax)
	{
		while ((y + 1) < map->ymax)
		{
			map->vertex1 = get_vertex(x, y, &map->vertex1, map);
			map->vertex2 = get_vertex(x, y + 1, &map->vertex2, map);
			display_line(display, &map->vertex1, &map->vertex2);
			y++;
		}
		y = 0;
		x++;
	}
}

void	display_all(t_display *display, t_map *map)
{
	int	x;
	int	y;

	x = map->xmax - 1;
	y = map->ymax - 1;
	while (x > 0)
	{
		while (y > 0)
		{
			map->vertex1 = get_vertex(x, y, &map->vertex1, map);
			map->vertex2 = get_vertex(x, (y - 1), &map->vertex2, map);
			display_line(display, &map->vertex1, &map->vertex2);
			map->vertex1 = get_vertex((x - 1), y, &map->vertex1, map);
			map->vertex2 = get_vertex(x, y, &map->vertex2, map);
			display_line(display, &map->vertex1, &map->vertex2);
			y--;
		}
		y = map->ymax - 1;
		x--;
	}
}

void	display_line(t_display *display, t_vertex *v1, t_vertex *v2)
{
	float		pad;
	t_vertex	curr_v;
	float		offset;

	offset = 0;
	curr_v.x = v1->x;
	curr_v.y = v1->y;
	curr_v.color = v1->color;
	pad = ((float)(v2->x - v1->x) / (float)(v2->y - v1->y));
	while (curr_v.x != v2->x || curr_v.y != v2->y)
	{
		if ((int)offset == 0)
			offset += pad;
		mlx_pixel_put(display->mlx, display->win, curr_v.x, curr_v.y,
			curr_v.color);
		curr_v = update_vertex(&curr_v, v2, &offset, pad);
	}
}
