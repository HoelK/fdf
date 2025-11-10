/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:38:32 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/10 22:08:17 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_display	init_display(t_display *display)
{
	display->mlx = mlx_init();
	display->win = mlx_new_window(display->mlx, 1920, 1080, "Window");
	return (*display);
}

int	mlx_safekill(t_display *display)
{
	mlx_destroy_window(display->mlx, display->win);
	mlx_destroy_display(display->mlx);
	free(display->mlx);
	free_coordinates(display->map->coordinates);
	exit (0);
}

int	handle_input(int keypress, t_display *display)
{
	if (keypress == XK_Escape)
		mlx_safekill(display);
	return (0);
}

int	mlx_close(t_display *display, t_map *map)
{
	display->map = map;
	mlx_key_hook(display->win, handle_input, display);
	mlx_hook(display->win, 17, 1L << 2, mlx_safekill, display);
	return (0);
}
