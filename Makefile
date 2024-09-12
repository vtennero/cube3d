# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS = -Wall -Wextra -Werror -g
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address

# Audio flags
AUDIOFLAGS = -lopenal -lmpg123

# Directories
SRC_DIR = src
LIBFT_DIR = libft
MLX_DIR = mlx
OBJ_DIR = obj
AUDIO_LIB_DIR = audio_lib

# Name of the final executables
NAME = cub3D
BONUS_NAME = cub3D_bonus
HELLDIVER_NAME = helldivers3D

# Main source file variable
MAIN = main.c
BONUS_MAIN = main_bonus.c
HELLDIVER_MAIN = main_bonus.c

SHARED_SRCS = \
check_map_boundaries.c \
check_map_boundaries_helper.c \
debug_utils.c \
enemies_attack_bonus00.c \
enemies_attack_bonus01.c \
enemies_attack_bonus02.c \
enemies_movement_bonus00.c \
extract_bonus.c \
gameplay_item_collection_bonus00.c \
gameplay_movement00.c \
gameplay_movement_bonus00.c \
gameplay_movement_bonus01.c \
gameplay_movement_bonus02.c \
gameplay_movement_bonus03.c \
initialization00.c \
initialization_bonus00.c \
initialization_bonus01.c \
initialization_bonus02.c \
interface_crosshair_bonus.c \
interface_health_bar_bonus.c \
intro_bonus00.c \
intro_bonus01.c \
intro_bonus02.c \
map_parse_utility.c \
menu_bonus.c \
movement_mouse.c \
napalm_bonus.c \
outro_bonus.c \
parse_map.c \
pelican_inside_bonus.c \
randomizer.c \
randomizer_bonus00.c \
raycasting.c \
raycasting_utils.c \
render.c \
render_bonus00.c \
render_bonus01.c \
render_bonus02.c \
render_bonus03.c \
render_bonus04.c \
render_collectibles.c \
render_enemies.c \
render_floor_bonus.c \
render_gun.c \
render_objects.c \
render_sky_floor.c \
render_sky_bonus.c \
render_walls.c \
render_walls_bonus.c \
respawn_bonus.c \
scripts.c \
scripts_bonus00.c \
scripts_static.c \
strike_bonus.c \
supplies_bonus.c \
terminate01.c \
terminate02.c \
terminate03.c \
texture_parse.c \
texture_parse_02.c \
textures_load00.c \
textures_load_bonus00.c \
textures_load_bonus01.c \
textures_load_bonus02.c \
textures_load_bonus03.c \
textures_load_bonus04.c

SHARED_SRCS := $(SHARED_SRCS:%=$(SRC_DIR)/%)

# Object files for main, bonus, and helldiver executables
OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(MAIN:.c=.o)) $(OBJ_DIR)/audio_dummy.o
BONUS_OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(BONUS_MAIN:.c=.o)) $(OBJ_DIR)/audio_dummy.o
HELLDIVER_OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(HELLDIVER_MAIN:.c=.o)) $(OBJ_DIR)/audio_bonus.o


# Include paths
INCLUDES = -I$(LIBFT_DIR) -I$(MLX_DIR) -I/usr/include -I$(SRC_DIR)

# MLX Flags
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm

# Libft compilation rule
LIBFT = $(LIBFT_DIR)/libft.a

# MLX library
MLX_LIB = $(MLX_DIR)/libmlx_$(shell uname).a

.PHONY: all bonus helldiver clean fclean re

all: $(LIBFT) $(MLX_LIB) $(NAME)

bonus: $(LIBFT) $(MLX_LIB) $(BONUS_NAME)

helldivers3d: $(LIBFT) $(MLX_LIB) $(HELLDIVER_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -include $(SRC_DIR)/cube3d.h

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $@ -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -include $(SRC_DIR)/cube3d.h -include $(SRC_DIR)/cube3d_bonus.h

$(HELLDIVER_NAME): $(HELLDIVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -DHELLDIVER $(HELLDIVER_OBJS) -o $@ -L$(LIBFT_DIR) -lft $(MLX_FLAGS) $(AUDIOFLAGS) -include $(SRC_DIR)/cube3d.h -include $(SRC_DIR)/cube3d_bonus.h -include $(SRC_DIR)/cube3d_audio_bonus.h

clean:
	rm -f $(OBJ_DIR)/*.o
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(HELLDIVER_NAME)
	rm -rf $(AUDIO_LIB_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
