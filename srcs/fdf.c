#include "fdf.h"

/*void	test_draw(t_display *display)
{
	t_vertex	v1;
	t_vertex	v2;

	v1.x = 0;
	v1.y = 0;
	v2.x = 0;
	v2.y = 200;
	display_line(display, &v1, &v2);
	v1.x = 0;
	v1.y = 200;
	v2.x = 200;
	v2.y = 200;
	display_line(display, &v1, &v2);
	v1.x = 0;
	v1.y = 200;
	v2.x = 200;
	v2.y = 200;
	display_line(display, &v1, &v2);
	v1.x = 200;
	v1.y = 0;
	v2.x = 200;
	v2.y = 200;
	display_line(display, &v1, &v2);
	v1.x = 200;
	v1.y = 0;
	v2.x = 0;
	v2.y = 0;
	display_line(display, &v1, &v2);
	v1.x = 0;
	v1.y = 0;
	v2.x = 200;
	v2.y = 200;
	display_line(display, &v1, &v2);
	v1.x = 0;
	v1.y = 200;
	v2.x = 200;
	v2.y = 0;
	display_line(display, &v1, &v2);
	v1.x = 494;
	v1.y = 221;
	v2.x = 31;
	v2.y = 1400;
	display_line(display, &v1, &v2);
}*/

int	main(int argc, char **argv)
{
	t_display	display;
	t_map		map;

	if (argc != 2)
		error_handle(argc);
	map.coordinates = get_coordinate(argv[1], &map);
	display = init_display(&display);

	//printf("dec : %ld\n", strhex_to_ulong("0x802020"));
	display_map(&display, &map);
	//test_draw(&display);

	mlx_close(&display, &map);
	mlx_loop(display.mlx);
	free_coordinates(map.coordinates);
	return (0);
}
