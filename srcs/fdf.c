/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:11:51 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/10 21:11:42 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_display	display;
	t_map		map;

	if (argc != 2)
		error_handle(argc);
	map = init_map(argv[1]);
	display = init_display(&display);
	display_map(&display, &map);
	mlx_close(&display, &map);
	mlx_loop(display.mlx);
	free_coordinates(map.coordinates);
	return (0);
}
