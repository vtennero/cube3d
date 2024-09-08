# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address



# Audio flags
AUDIOFLAGS = -lopenal -lmpg123
# AUDIOFLAGS = 

# Directories
SRC_DIR = src
LIBFT_DIR = libft
MLX_DIR = mlx
OBJ_DIR = obj
AUDIO_LIB_DIR = audio_lib

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
render_walls_bonus.c \
render_sky.c \
render_gun.c \
render_collectibles.c \
render_objects.c \
supplies_bonus.c \
render_enemies.c \
raycasting.c \
raycasting_utils.c \
movement.c \
movement_mouse.c \
movement_enemies.c \
textures.c \
movement_player_reloc.c \
randomizer.c \
tmp_staticmap.c \
keymap_collectibles.c \
terminate01.c \
terminate02.c \
terminate03.c \
menu_bonus.c \
opening_bonus.c \
land_bonus.c \
outro_bonus.c \
time.c \
extract_bonus.c \
respawn_bonus.c \
scripts.c \
scripts_static.c \
enemies_hit_bonus.c \
strike_bonus.c \
check_map_boundaries.c \
flood_fill_helper.c\
map_parse_utility.c \
parse_map.c  \
texture_parse.c \
texture_parse_02.c \
pelican_inside_bonus.c \
health_bar_bonus.c \
audio_bonus.c \
# audio_dummy.c \



SHARED_SRCS := $(SHARED_SRCS:%=$(SRC_DIR)/%)

# Object files for main and bonus executables
OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(MAIN:.c=.o))
BONUS_OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(BONUS_MAIN:.c=.o))

# Include paths
INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR) -I/usr/include

# MLX Flags
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

# Libft compilation rule
LIBFT = $(LIBFT_DIR)/libft.a

# MLX library
MLX_LIB = $(MLX_DIR)/libmlx_$(shell uname).a

.PHONY: all clean fclean re bonus

all: $(LIBFT) $(MLX_LIB) $(NAME) copy_libs

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIBFT_DIR) -lft $(MLX_FLAGS) $(AUDIOFLAGS)

copy_libs:
	@mkdir -p $(AUDIO_LIB_DIR)
	@cp /usr/lib/x86_64-linux-gnu/libopenal.so.1 $(AUDIO_LIB_DIR)/ || true
	@cp /usr/lib/x86_64-linux-gnu/libmpg123.so.0 $(AUDIO_LIB_DIR)/ || true

bonus:
	$(MAKE) MAIN=$(BONUS_MAIN) NAME=$(BONUS_NAME) all

clean:
	rm -f $(OBJ_DIR)/*.o
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	rm -rf $(AUDIO_LIB_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all