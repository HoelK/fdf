#include <stdio.h>
#include <math.h>
#include "minilibx-linux/mlx.h"

void	print_data(int p1_x, int p1_y, int p2_x, int p2_y)
{
	printf("1 co : %d\n", p2_y - p1_y);
	printf("2 co : %d\n", p2_x - p1_x);
	printf("tu co : %d\n", ((p2_y - p2_x) / (p1_x - p1_y)));
	printf("pad co : %d\n", ((p2_y - p1_y) / (p2_x - p1_x)));
	printf("pad co : %d\n", ((p1_x - p2_x) / (p1_y - p2_y)));
}

void	test_print(int p1_x, int p1_y, int p2_x, int p2_y)
{
	int current_x;
	int current_y;
	void	*mlx;
	void	*mlx_win;
	//int	tmp;
	int	pad;

	/*if (p2_x < p1_x)
	{
		tmp = p1_x;
		p1_x = p2_x;
		p2_x = tmp;
	}
	if (p2_y < p1_y)
	{
		tmp = p1_y;
		p1_y = p2_y;
		p2_y = tmp;
	}*/
	current_x = p1_x;
	current_y = p1_y;
	mlx = mlx_init();
	pad = ((p2_x - p1_x) / (p2_y - p1_y));
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	while (current_x != p2_x || current_y != p2_y)
	{
		mlx_pixel_put(mlx, mlx_win, current_x, current_y, 0x00FF0000);
		if (current_x != p2_x)
			current_x++;
		if (current_y % pad == 0 && current_y != p2_y)
			current_y++;
		printf("=====CO=====\ncurrent_x : %d\ncurrent_y : %d\ncurrent co : %d\npad : %d\n", current_x, current_y, current_x - current_y, pad);
	}
	print_data(p1_x, p1_y, p2_x, p2_y);
	mlx_loop(mlx);
}

int	main(void)
{
	test_print(500, 500, 660, 600);
}
