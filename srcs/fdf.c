#include "fdf.h"

int	main(int argc, char **argv)
{
	t_display	display;
	t_map		map;

	if (argc != 2)
		error_handle(argc);
	map.coordinates = get_coordinate(argv[1], &map);
	display = init_display(&display);

	//display_map(&display, &map);
	//test_print(1, 700, 1000, 10);

	display_x(&display, &map);
	display_y(&display, &map);
	//display_line(&display, &map.vertex1, &map.vertex2);

	mlx_loop(display.mlx);
	mlx_close(&display);
	free_coordinates(map.coordinates);
	return (0);
}
