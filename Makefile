CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = cube3d
SRCS = main.c # Add any other source files here
OBJS = $(SRCS:.c=.o)

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	INCLUDES = -I/opt/X11/include -Imlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(shell uname).a

all: $(MLX_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX_FLAGS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	@make -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
