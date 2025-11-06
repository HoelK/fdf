#include "minilibx-linux/mlx.h"
#include <math.h>
#include <stdio.h>

void	print_data(float p1_x, float p1_y, float p2_x, float p2_y, float pad)
{
	printf("p1_x : %f\np1_y: %f\n", p1_x, p1_y);
	printf("p2_x : %f\np2_y: %f\n", p2_x, p2_y);
	printf("tu co : %f\n", pad);
}

void	test_print(float p1_x, float p1_y, float p2_x, float p2_y)
{
	float current_x;
	float current_y;
	float pad;
	void	*mlx;
	void	*mlx_win;

	current_x = p1_x;
	current_y = p1_y;
	mlx = mlx_init();
	pad = ((p2_x - p1_x) / (p2_y - p1_y));
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	print_data(p1_x, p1_y, p2_x, p2_y, pad);
	while (current_x <= p2_x || current_y <= p2_y)
	{
		mlx_pixel_put(mlx, mlx_win, current_x, current_y, 0x00FF0000);
		if (current_x != p2_x)
			current_x += 1;
		if ((fmod(current_x, pad)) == (float)0 && current_y != p2_y)
			current_y += 1;
		printf("=====CO=====\ncurrent_x : %f\ncurrent_y : %f\npad : %f\n", current_x, current_y, pad);
		print_data(p1_x, p1_y, p2_x, p2_y, pad);
	}
	print_data(p1_x, p1_y, p2_x, p2_y, pad);
	mlx_loop(mlx);
}

int	main(void)
{

	//test_print(500, 500, 800, 700);

	int	i;
	float	offset;
	float	pixel;

	i = 0;
	pixel = 0;
	offset = 1.875;
	while (i < 10)
	{
		pixel += offset;
		printf("pixel before minus :%f\n", pixel);
		pixel -= (int)pixel;
		printf("pixel after minus :%f\n", pixel);
		i++;
	}
}
