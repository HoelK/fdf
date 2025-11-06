CC=cc
FLAGS=-Werror -Wextra -Wall -g
DIR=srcs
SRCS=$(DIR)/display_line.c $(DIR)/fdf.c $(DIR)/display_management.c $(DIR)/parse.c
OBJS=$(DIR)/display_line.o $(DIR)/fdf.o $(DIR)/display_management.o $(DIR)/parse.o
NAME=fdf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -Lmlx_linux -lmlx_Linux -L./minilibx-linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
