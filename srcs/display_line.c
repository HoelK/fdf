#include "fdf.h"

void	print_data(float p1_x, float p1_y, float p2_x, float p2_y, float pad)
{
	printf("p1_x : %f\np1_y: %f\n", p1_x, p1_y);
	printf("p2_x : %f\np2_y: %f\n", p2_x, p2_y);
	printf("tu co : %f\n", pad);
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

int	ft_ishex(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

unsigned long	strhex_to_ulong(char *str)
{
	int		i;
	unsigned long	result;

	i = 0;
	result = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\n' && ft_ishex(str[i]))
	{
		if (str[i] >= 'a' && str[i] <= 'f')
			result += 9 + (str[i] - 'b');
		else if (str[i] >= 'A' && str[i] <= 'F')
			result += 9 + (str[i] - 'B');
		else
			result += str[i] - '0';
		if (str[i + 1] && str[i + 1] != ' ' && str[i + 1] != '\n' && ft_ishex(str[i + 1]))
			result *= 16;
		i++;
	}
	return (result);

}

t_vertex	get_iso(int x, int y, t_vertex *v, t_map *map)
{
	int	z;
	float	tmp;

	v->x = get_vertex(x, map->ymax);
	v->y = get_vertex(y, map->ymax);
	z = get_vertex(map->coordinates[y][x], map->ymax);
	
	tmp = v->x;
	v->x = (v->x - v->y) * cos(0.523599) + 600;
	v->y = ((tmp + v->y) * sin(0.523599)) - z + 100;
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
			display_line(display, &map->vertex1, &map->vertex2, map->colors[y][x]);
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
			display_line(display, &map->vertex1, &map->vertex2, map->colors[y][x]);
			y++;
		}
		y = 0;
		x++;
	}
}

void	display_line(t_display *display, t_vertex *v1, t_vertex *v2, unsigned long color)
{
	t_vertex	curr_v;
	float		x_sign;
	float		y_sign;
	float		pad;
	float		offset;

	offset = 0;
	curr_v.x = v1->x;
	curr_v.y = v1->y;
	x_sign = (v2->x - v1->x);
	y_sign = (v2->y - v1->y);
	pad = x_sign / y_sign;
	while (curr_v.x != v2->x || curr_v.y != v2->y)
	{
		if ((int)offset == 0)
			offset += pad;
		mlx_pixel_put(display->mlx, display->win, curr_v.x, curr_v.y, color);
		if (curr_v.x != v2->x && (int)offset != 0)
		{
			if (x_sign < 0)
				curr_v.x--;
			if (x_sign > 0)
				curr_v.x++;
			if (pad < 0)
				offset++;
			if (pad > 0)
				offset--;
		}
		if (curr_v.y != v2->y && (int)offset == 0)
		{
			if (y_sign < 0)
				curr_v.y--;
			if (y_sign > 0)
				curr_v.y++;
		}
		printf("current y : %d\ncurrent x : %d\nv2 y : %d\nv2 x : %d\n", curr_v.y, curr_v.x, v2->y, v2->x);
	}
}
