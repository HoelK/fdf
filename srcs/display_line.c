#include "fdf.h"

void	display_map(t_display *display, t_map *map)
{
	//display_x(display, map);
	//display_y(display, map);
	display_all(display, map);
}

int	map_vertex(int i, int max, char mod)
{
	float	res;
	
	res = ((float)RES_X / (float)RES_Y);
	if (mod == 'y')
		return (i * ((RES_Y / res) / max));
	if (mod == 'x')
		return (i * ((RES_X / (res * res)) / max));
	if (mod == 'z')
		return (i * ((RES_Y / (res * res * res)) / max));
	return (0);
}

t_vertex	get_vertex(int x, int y, t_vertex *v, t_map *map)
{
	int	z;
	float	tmp;
	float	res;

	v->x = map_vertex(x, map->ymax, 'x');
	v->y = map_vertex(y, map->ymax, 'y');
	z = map_vertex(map->coordinates[y][x], map->ymax, 'z');
	v->color = map->colors[y][x];
	tmp = v->x;
	res = ((float)RES_X / (float)RES_Y);
	v->x = (v->y + tmp) * cos(0.523599);
	v->y = ((v->y - tmp) * sin(0.523599)) - z;
	v->x += (RES_X / (res * res * res));
	v->y += (RES_Y / (res));
	return (*v);
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

t_vertex	update_vertex(t_vertex *curr_v, t_vertex *final_v, float *offset, float pad)
{
	float	x_add;
	float	y_add;
	unsigned long	off_color;

	off_color = (final_v->color - curr_v->color);
	x_add = ((final_v->x - curr_v->x) / abs(final_v->x - curr_v->x));
	y_add = ((final_v->y - curr_v->y) / abs(final_v->y - curr_v->y));
	if (curr_v->x != final_v->x && (int)(*offset) != 0)
	{
		curr_v->x += x_add;
		if (pad < 0)
			(*offset)++;
		if (pad > 0)
			(*offset)--;
	}
	if (curr_v->y != final_v->y && (int)(*offset) == 0)
		curr_v->y += y_add;
	curr_v->color += off_color;
	return (*curr_v);
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
		mlx_pixel_put(display->mlx, display->win, curr_v.x, curr_v.y, curr_v.color);
		curr_v = update_vertex(&curr_v, v2, &offset, pad);
		printf("current y : %d\ncurrent x : %d\ncurrent color : %ld\nv2 color : %ld\nv2 y : %d\nv2 x : %d\noffset : %f\npad : %f\n", curr_v.y, curr_v.x, curr_v.color, v2->color, v2->y, v2->x, offset, pad);
	}
}
