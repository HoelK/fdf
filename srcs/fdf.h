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
#define RES_X 1920
#define RES_Y 1080


typedef struct s_vertex
{
	int	x;
	int	y;
}	t_vertex;

typedef struct s_map
{
	int		xmax;
	int		ymax;
	t_vertex	vertex1;
	t_vertex	vertex2;
	int		**coordinates;
	unsigned long		**colors;
}	t_map;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_map	*map;
}	t_display;

//memory
void	free_all(char **strs);
void	free_coordinates(int **coordinates);
int	mlx_safekill(t_display *display);

//file parse
char	**get_file(char *file_path);
int	count_lines(char *file_path);

//coordinate parse
int	count_coordinates(char *str);
int	**parse_coordinates(char **file, unsigned long ***colors, int nx, int ny);
int	*fill_coordinates(char *str, int *coordinates, unsigned long *colors, int nx);
int	**get_coordinate(char *file_path, t_map *map);

//utils
int	ft_isnum(char c);
int	ft_ishex(char c);
unsigned long	strhex_to_ulong(char *str);

//display management
t_display	init_display(t_display *display);
int	mlx_close(t_display *display, t_map *map);
int	handle_input(int keypress, t_display *display);

//draw
void	display_all(t_display *display, t_map *map);
void	display_line(t_display *display, t_vertex *v1, t_vertex *v2, unsigned long color);
void	display_map(t_display *display, t_map *map);
void	display_y(t_display *display, t_map *map);
void	display_x(t_display *display, t_map *map);

void	error_handle(int argc);
void	print_data(float p1_x, float p1_y, float p2_x, float p2_y, float pad);
void	test_print(float p1_x, float p1_y, float p2_x, float p2_y);

#endif
