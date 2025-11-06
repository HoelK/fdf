#include "fdf.h"

int	main(int argc, char **argv)
{
	t_display	display;
	int		**coordinates;

	if (argc != 2)
		error_handle(argc);
	coordinates = get_coordinate(argv[1]);
	display = init_display(&display);

	test_print(1, 700, 1000, 10);

	mlx_loop(display.mlx);
	mlx_destroy_display(display.mlx);
	free_coordinates(coordinates);
	return (0);
}
