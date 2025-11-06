#include "fdf.h"

t_display	init_display(t_display *display)
{
	display->mlx = mlx_init();
	display->win = mlx_new_window(display.mlx, 1920, 1080, "Window");
}

int	mlx_safekill(display_t *display)
{
        mlx_destroy_window(display->mlx, display->win);
	mlx_destroy_display(display->mlx);
	free(display->mlx);
	exit(0);
}

int	handle_input(int keypress, display_t *display)
{
    if (keypress == XK_Escape)
	    mlx_safekill(display);
    return (0);
}

int	mlx_close(display_t *display)
{
	mlx_key_hook(display->win, handle_input, display);
	mlx_hook(display->win, 17, 1L<<2, mlx_safekill, display);
	return (0);
}
