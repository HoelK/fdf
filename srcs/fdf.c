#include "fdf.h"

int	main(int argc, char **argv)
{
	t_display	display;
	t_map		map;

	if (argc != 2)
		error_handle(argc);
	map.coordinates = get_coordinate(argv[1], &map);
	display = init_display(&display);
	display_map(&display, &map);
	mlx_close(&display, &map);
	mlx_loop(display.mlx);
	free_coordinates(map.coordinates);
	return (0);
}
