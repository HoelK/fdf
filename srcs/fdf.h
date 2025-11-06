
#ifndef FDF_H
# define FDF_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <X11/keysym.h>
#include "../minilibx-linux/mlx.h"
#include "../gnl/get_next_line.h"

typedef struct s_display
{
	void	*mlx;
	void	*win;
}	t_display;

void	free_coordinates(int **coordinates);
void	print_data(float p1_x, float p1_y, float p2_x, float p2_y, float pad);
void	ft_swap(float *a, float *b);
void	test_print(float p1_x, float p1_y, float p2_x, float p2_y);
void	free_all(char **strs);
int	count_lines(char *file_path);
void	error_handle(int argc);
char	**get_file(char *file_path);
int	ft_isnum(char c);
int	count_coordinates(char *str);
void	safe_kill(int **tab1, char **tab2);
int	*fill_coordinates(char *str, int *to_fill);
int	**parse_coordinate(char **file, int nx, int ny);
t_display	init_display(t_display *display);
int	mlx_safekill(t_display *display);
int	handle_input(int keypress, t_display *display);
int	mlx_close(t_display *display);
int	**get_coordinate(char *file_path);

#endif
