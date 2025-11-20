/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 20:11:51 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/20 05:53:31 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		kill_error(path);
	close(fd);
}

int	main(int argc, char **argv)
{
	t_display	display;
	t_map		map;

	if (argc != 2)
		error_handle(argc);
	check_file(argv[1]);
	display = init_display(&display);
	map = init_map(argv[1]);
	display_map(&display, &map);
	mlx_close(&display, &map);
	mlx_loop(display.mlx);
	free_coordinates(map.coordinates);
	return (0);
}
