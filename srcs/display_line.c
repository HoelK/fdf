#include "fdf.h"

void	print_data(float p1_x, float p1_y, float p2_x, float p2_y, float pad)
{
	printf("p1_x : %f\np1_y: %f\n", p1_x, p1_y);
	printf("p2_x : %f\np2_y: %f\n", p2_x, p2_y);
	printf("tu co : %f\n", pad);
}

void	ft_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	display_map(t_display *display, t_map *map)
{
	display_x(display, map);
	display_y(display, map);
}

int	get_vertex(int i, int max)
{
	//2d formula
	return (100 + i * ((RES_Y - 400) / max));
}

t_vertex	get_iso(int x, int y, t_vertex *v, t_map *map)
{
	v->x = get_vertex(x, map->ymax);
	v->y = get_vertex(y, map->ymax);
	
	float tmp = v->x;
	v->x = (v->x + v->y) * cos(0.523599);
	//v->y = ((v->y - tmp) * sin(0.523599)) + 400; //BETTER ANGLE, BAD LINES ??
	v->y = (v->y * sin(0.523599) - map->ymax * 2) + 400;
	
	//v->x = (v->x + v->y) * cos(0.523599) + 100;
	//v->y = (v->x - v->y) * sin(0.523599) + 300;
	
	//v->x = ((v->x - v->y) * cos(0.5));
	//v->y = ((v->x + v->y) * sin(0.5));
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
			map->vertex1 = get_iso(x, y, &map->vertex1, map);
			map->vertex2 = get_iso(x + 1, y, &map->vertex2, map);
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
			map->vertex1 = get_iso(x, y, &map->vertex1, map);
			map->vertex2 = get_iso(x, y + 1, &map->vertex2, map);
			display_line(display, &map->vertex1, &map->vertex2);
			y++;
		}
		y = 0;
		x++;
	}
}

void	fix_vertexs(t_vertex *v1, t_vertex *v2)
{
	if (v2->x < v1->x)
		ft_swap(&v2->x, &v1->x);
	if (v2->y < v1->y)
		ft_swap(&v2->y, &v1->y);
	if (v1->x == v2->x)
		v2->x++;
	if (v1->y == v2->y)
		v2->y++;
}

void	display_line(t_display *display, t_vertex *v1, t_vertex *v2)
{
	float		pad;
	float		offset;
	t_vertex	current_v;

	offset = 0;
	fix_vertexs(v1, v2);
	current_v.x = v1->x;
	current_v.y = v1->y;
	pad = ((v2->x - v1->x) / (v2->y - v1->y));
	while (current_v.x < v2->x || current_v.y < v2->y)
	{
		if (offset < (int)1)
			offset += pad;
		mlx_pixel_put(display->mlx, display->win, current_v.x, current_v.y, 0x00FF0000);
		if ((int)offset > 0 && current_v.x != v2->x)
		{
			current_v.x += 1;
			offset -= (int)1;
		}
		if ((int)offset == 0 && current_v.y != v2->y)
			current_v.y += 1;
	}
}
