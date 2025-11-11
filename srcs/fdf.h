/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkeromne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:50:16 by hkeromne          #+#    #+#             */
/*   Updated: 2025/11/11 22:19:23 by hkeromne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# define RES_X 1920
# define RES_Y 1080

typedef struct s_vertex
{
	int				x;
	int				y;
	int				color;
}	t_vertex;

typedef struct s_map
{
	int				xmax;
	int				ymax;
	t_vertex		vertex1;
	t_vertex		vertex2;
	int				**coordinates;
	int				**colors;
}	t_map;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		endian;
	int		line_len;
	int		bits_per_px;
}	t_img;

typedef struct s_display
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	img;
}	t_display;

//memory
void			free_all(char **strs);
void			free_coordinates(int **coordinates);
int				mlx_safekill(t_display *display);

//file parse
char			**get_file(char *file_path);
int				count_lines(char *file_path);

//coordinate parse
t_map			init_map(char *file_path);
int				count_coordinates(char *str);
int				**parse_coordinates(char **file, int ***colors,
					int nx, int ny);
int				*fill_coordinates(char *str, int *coordinates,
					int *colors, int nx);
int				**get_coordinate(char *file_path, t_map *map);

//utils
int				ft_isnum(char c);
int				ft_ishex(char c);
int				ft_atoi(const char *nptr);
int				str_to_color(char *str);

//display management
t_display		init_display(t_display *display);
int				mlx_close(t_display *display, t_map *map);
int				handle_input(int keypress, t_display *display);

//draw
void			display_all(t_display *display, t_map *map);
void			display_line(t_display *display, t_vertex *v1, t_vertex *v2);
void			display_map(t_display *display, t_map *map);
void			display_y(t_display *display, t_map *map);
void			display_x(t_display *display, t_map *map);
void			mlx_img_pixel_put(t_img *img, int x, int y, int color);

void			error_handle(int argc);
void			test_print(float p1_x, float p1_y, float p2_x, float p2_y);

//vertexs
int				map_vertex(int i, int max, char mod);
t_vertex		get_vertex(int x, int y, t_vertex *v, t_map *map);
t_vertex		update_v(t_vertex *curr_v, t_vertex *v2, float *offset,
					float pad);
void			update_color(t_vertex *v1, t_vertex *v2, t_vertex *curr_v);

//Mem safe
void			free_doublestr(char **strs);
void			free_coordinates(int **coordinates);
void			safe_kill(char **tab1, int **tab2, int **tab3);

#endif
