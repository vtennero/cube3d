# Compiler and flags
# CC = gcc -g
# without debugger:
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AUDIOFLAGS = -lopenal -lmpg123

# Directories
SRC_DIR = src
LIBFT_DIR = libft
MLX_DIR = mlx
OBJ_DIR = obj

# Name of the final executable
NAME = cube3d
BONUS_NAME = cube3d_bonus

# Main source file variable
MAIN = main.c
BONUS_MAIN = main_bonus.c

# Shared source files
SHARED_SRCS = debug_utils.c \
initialization.c \
render.c \
render_floor.c \
render_walls.c \
render_sky.c \
render_gun.c \
render_objects.c \
raycasting.c \
raycasting_utils.c \
movement.c \
movement_mouse.c \
textures.c \
movement_player_reloc.c \
randomizer.c \
tmp_staticmap.c

SHARED_SRCS := $(SHARED_SRCS:%=$(SRC_DIR)/%)

# Object files for main and bonus executables
OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(MAIN:.c=.o)
BONUS_OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(BONUS_MAIN:.c=.o)

# Include paths
INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR)  -I/usr/include

# MLX Flags
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

# Libft compilation rule
LIBFT = $(LIBFT_DIR)/libft.a

# MLX library
MLX_LIB = $(MLX_DIR)/libmlx_$(shell uname).a

.PHONY: all clean fclean re bonus

all: $(LIBFT) $(MLX_LIB) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIBFT_DIR) -lft $(MLX_FLAGS) $(AUDIOFLAGS)

bonus:
	$(MAKE) MAIN=$(BONUS_MAIN) NAME=$(BONUS_NAME) all

clean:
	rm -f $(OBJ_DIR)/*.o
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
