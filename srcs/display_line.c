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

int	get_vertex(int start, int i, int max)
{
	return (start + (i * ((RES_Y - (start * 2)) / max)));
}

void	display_y(t_display *display, t_map *map)
{
	int		x;
	int		y;
	int		start;

	x = 0;
	y = 0;
	start = 100;
	while (x < map->xmax)
	{
		while ((y + 1) < map->ymax)
		{
			map->vertex1.x = get_vertex(start, x, map->ymax);
			map->vertex2.x = get_vertex(start, x, map->ymax);
			map->vertex1.y = get_vertex(start, y, map->ymax);
			map->vertex2.y = get_vertex(start, y + 1, map->ymax);
			display_line(display, &map->vertex1, &map->vertex2);
			printf("vertex x : %d\n", get_vertex(start, x, map->xmax));
			printf("vertex y : %d\n", get_vertex(start, y, map->ymax));
			printf("vertex y + 1: %d\n", get_vertex(start, y + 1, map->ymax));
			printf("xmax : %d\n", map->xmax);
			printf("ymax : %d\n", map->ymax);
			y++;
		}
		y = 0;
		x++;
	}
}

void	display_x(t_display *display, t_map *map)
{
	int		x;
	int		y;
	int		start;

	x = 0;
	y = 0;
	start = 100;
	while (y < map->ymax)
	{
		while ((x + 1) < map->xmax)
		{
			map->vertex1.y = get_vertex(start, y, map->ymax);
			map->vertex2.y = get_vertex(start, y, map->ymax);
			map->vertex1.x = get_vertex(start, x, map->ymax);
			map->vertex2.x = get_vertex(start, x + 1, map->ymax);
			display_line(display, &map->vertex1, &map->vertex2);
			printf("vertex x : %d\n", get_vertex(start, x, map->xmax));
			printf("vertex y : %d\n", get_vertex(start, y, map->ymax));
			printf("vertex y + 1: %d\n", get_vertex(start, y + 1, map->ymax));
			printf("xmax : %d\n", map->xmax);
			printf("ymax : %d\n", map->ymax);
			x++;
		}
		x = 0;
		y++;
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

void	test_print(float p1_x, float p1_y, float p2_x, float p2_y)
{
	float current_x;
	float current_y;
	float pad;
	void	*mlx;
	void	*mlx_win;
	float	offset;

	if (p2_x < p1_x)
		ft_swap(&p2_x, &p1_x);
	if (p2_y < p1_y)
		ft_swap(&p2_y, &p1_y);
	offset = 0;
	current_x = p1_x;
	current_y = p1_y;
	mlx = mlx_init();
	pad = (fabs(p2_x - p1_x) / fabs(p2_y - p1_y));
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	print_data(p1_x, p1_y, p2_x, p2_y, pad);
	while (current_x < p2_x || current_y < p2_y)
	{
		if (offset < (int)1)
			offset += pad;
		mlx_pixel_put(mlx, mlx_win, current_x, current_y, 0x00FF0000);
		if ((int)offset > 0 && current_x != p2_x)
		{
			current_x += 1;
			offset -= (int)1;
		}
		if ((int)offset == 0 && current_y != p2_y)
			current_y += 1;
		printf("=====CO=====\ncurrent_x : %f\ncurrent_y : %f\npad : %f\noffset : %f\n", current_x, current_y, pad, offset);
		print_data(p1_x, p1_y, p2_x, p2_y, pad);

	}
	mlx_pixel_put(mlx, mlx_win, p1_x, p1_y, 0xFFFFFFFF);
	mlx_pixel_put(mlx, mlx_win, p2_x, p2_y, 0xFFFFFFFF);
	print_data(p1_x, p1_y, p2_x, p2_y, pad);
	mlx_loop(mlx);
}

