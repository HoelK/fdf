#include "fdf.h"

int	main(void)
{

	float p2_x = 500;
	float p2_y = 10;
	float p1_x = 700;
	float p1_y = 700;
	if (p2_x < p1_x)
		ft_swap(&p2_x, &p1_x);
	if (p2_y < p1_y)
		ft_swap(&p2_y, &p1_y);
	print_data(700, 700, 500, 10, (fabs(p2_x - p1_x) / fabs(p2_y - p1_y)));
	test_print(1, 700, 1000, 10);

	/*int	i;
	float	offset;
	float	pixel;

	i = 0;
	pixel = 0;
	offset = 1.875;
	while (i < 10)
	{
		if ((int)pixel < 1)
			pixel += offset;
		printf("pixel before minus :%f\n", pixel);
		pixel -= (int)1;
		printf("pixel after minus :%f\n", pixel);
		i++;
	}*/
}
