#include "fdf.h"

void	free_coordinates(int **coordinates)
{
	int	i;

	i = 0;
	while (coordinates[i] != NULL)
		free(coordinates[i++]);
	free(coordinates);
}

void	free_doublestr(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
		free(strs[i++]);
	free(strs);
}

int	ft_isnum(char c)
{
	return (c >= '0' && c <= '9');
}

int	count_coordinates(char *str)
{
	int	i;
	int	n_coo;

	i = 0;
	n_coo = 0;
	while (str[i] && str[i] != '\n')
	{
		while (str[i] && str[i] != '\n' && str[i] == ' ')
			i++;
		if (ft_isnum(str[i]))
			n_coo++;
		while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
			i++;
	}
	return (n_coo);
}

void	safe_kill(int **tab1, char **tab2)
{
	int	i;

	i = 0;
	while (tab1[i] != NULL)
		free(tab1[i++]);
	free(tab1);
	i = 0;
	while (tab2[i] != NULL)
		free(tab2[i++]);
	free(tab2);
	exit(0);
}

int	*fill_coordinates(char *str, int *to_fill)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
	{
		to_fill[j] = 0;
		while (str[i] && str[i] != '\n' && str[i] == ' ')
			i++;
		while (str[i] && str[i] != '\n' && ft_isnum(str[i]))
		{
			to_fill[j] += str[i] - '0';
			if (ft_isnum(str[i + 1]))
				to_fill[j] *= 10;
			i++;
		}
		j++;
	}
	return (to_fill);
}

int	**parse_coordinates(char **file, int nx, int ny)
{
	int	i;
	int	j;
	int	**coordinates;

	i = 0;
	j = 0;
	coordinates = malloc(sizeof(int *) * (nx + 1));
	if (coordinates == NULL)
		return (NULL);
	while (i < nx + 1)
		coordinates[i++] = NULL;
	i = 0;
	while (i < nx)
	{
		coordinates[i] = malloc(sizeof(int) * ny);
		if (coordinates[i] == NULL)
			safe_kill(coordinates, file);
		coordinates[i] = fill_coordinates(file[i], coordinates[i]);
		i++;
	}
	return (coordinates);
}

int	**get_coordinate(char *file_path)
{
	int	nx;
	int	ny;
	char	**file_content;
	int	**coordinates;

	file_content = get_file(file_path);
	nx = count_lines(file_path);
	ny = count_coordinates(file_content[0]);
	coordinates = parse_coordinates(file_content, nx, ny);
	free_doublestr(file_content);
	return (coordinates);
}

int	main(int argc, char **argv)
{
	//display_t	display;
	int		**coordinates;

	if (argc != 2)
		error_handle(argc);
	coordinates = get_coordinate(argv[1]);
	free_coordinates(coordinates);
	/*display = init_display(&display);


	print_data(700, 700, 500, 10, (fabs(p2_x - p1_x) / fabs(p2_y - p1_y)));
	test_print(1, 700, 1000, 10);

	mlx_loop(display.mlx);
	mlx_destroy_display(display.mlx);*/
	return (0);
}
