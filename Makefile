CC=cc
FLAGS=-Werror -Wextra -Wall -g3 -O3
DIR=srcs
SRCS=$(DIR)/display_line.c $(DIR)/fdf.c $(DIR)/display_management.c $(DIR)/file_parse.c $(DIR)/coordinate_parse.c gnl/get_next_line.c gnl/get_next_line_utils.c
OBJS=$(DIR)/display_line.o $(DIR)/fdf.o $(DIR)/display_management.o $(DIR)/file_parse.o $(DIR)/coordinate_parse.o gnl/get_next_line.o gnl/get_next_line_utils.o
NAME=fdf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Lmlx_linux -lmlx_Linux -L./minilibx-linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
