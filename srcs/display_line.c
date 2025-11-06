#include "fdf.h"

void	print_data(float p1_x, float p1_y, float p2_x, float p2_y, float pad)
{
	printf("p1_x : %f\np1_y: %f\n", p1_x, p1_y);
	printf("p2_x : %f\np2_y: %f\n", p2_x, p2_y);
	printf("tu co : %f\n", pad);
}

void	ft_swap(float *a, float *b)
{
	float tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	test_print(float p1_x, float p1_y, float p2_x, float p2_y)
{
	float current_x;
	float current_y;
	float pad;
	void	*mlx;
	void	*mlx_win;
	float	offset;

	if (p2_x < p1_x)
		ft_swap(&p2_x, &p1_x);
	if (p2_y < p1_y)
		ft_swap(&p2_y, &p1_y);
	offset = 0;
	current_x = p1_x;
	current_y = p1_y;
	mlx = mlx_init();
	pad = (fabs(p2_x - p1_x) / fabs(p2_y - p1_y));
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	print_data(p1_x, p1_y, p2_x, p2_y, pad);
	while (current_x < p2_x || current_y < p2_y)
	{
		if (offset < (int)1)
			offset += pad;
		mlx_pixel_put(mlx, mlx_win, current_x, current_y, 0x00FF0000);
		if ((int)offset > 0 && current_x != p2_x)
		{
			current_x += 1;
			offset -= (int)1;
		}
		if ((int)offset == 0 && current_y != p2_y)
			current_y += 1;
		printf("=====CO=====\ncurrent_x : %f\ncurrent_y : %f\npad : %f\noffset : %f\n", current_x, current_y, pad, offset);
		print_data(p1_x, p1_y, p2_x, p2_y, pad);

	}
	mlx_pixel_put(mlx, mlx_win, p1_x, p1_y, 0xFFFFFFFF);
	mlx_pixel_put(mlx, mlx_win, p2_x, p2_y, 0xFFFFFFFF);
	print_data(p1_x, p1_y, p2_x, p2_y, pad);
	mlx_loop(mlx);
}

