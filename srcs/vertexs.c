/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertexs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 22:12:55 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/10 22:39:37 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	int		z;
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

t_vertex	update_v(t_vertex *c_v, t_vertex *v2, float *offset, float pad)
{
	float			x_add;
	float			y_add;

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
	return (*curr_v);
}
