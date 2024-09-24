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

# Audio file variables
AUDIO_DUMMY_SRCS = audio_dummy00.c audio_dummy01.c
AUDIO_BONUS_SRCS = audio_bonus00.c audio_bonus01.c audio_bonus02.c

SHARED_SRCS = \
debug_utils.c \
gameplay_enemies_bonus00.c \
gameplay_enemies_bonus01.c \
gameplay_enemies_bonus02.c \
gameplay_enemies_bonus03.c \
gameplay_item_collection_bonus00.c \
gameplay_movement00.c \
gameplay_movement_bonus00.c \
gameplay_movement_bonus01.c \
gameplay_movement_bonus02.c \
gameplay_movement_bonus03.c \
gameplay_movement_bonus04.c \
gameplay_scripts_static_bonus00.c \
gameplay_scripts_static_bonus01.c \
gameplay_scripts_static_bonus02.c \
gameplay_scripts_static_bonus03.c \
gameplay_scripts_static_bonus04.c \
gameplay_scripts_static_bonus05.c \
gameplay_scripts_bonus00.c \
gameplay_scripts_bonus01.c \
gameplay_scripts_bonus02.c \
gameplay_scripts_bonus03.c \
render_effects_strike00_bonus00.c \
render_effects_strike00_bonus01.c \
render_effects_strike01_bonus00.c \
render_effects_strike01_bonus01.c \
render_effects_strike02_bonus00.c \
render_effects_strikes_bonus00.c \
initialization00.c \
initialization_bonus00.c \
initialization_bonus01.c \
initialization_bonus02.c \
render_scenes_bonus00.c \
render_scenes_bonus01.c \
render_scenes_bonus02.c \
render_scenes_bonus03.c \
render_scenes_bonus04.c \
parsing_boundaries_01.c \
parsing_boundaries_02.c \
parsing_map_00.c \
parsing_map_01.c \
parsing_map_texture_01.c \
parsing_map_texture_02.c \
parsing_map_utility.c \
randomizer_bonus00.c \
randomizer_bonus01.c \
raycasting00.c \
raycasting01.c \
raycasting02.c \
raycasting03.c \
raycasting04.c \
raycasting05.c \
raycasting06.c \
raycasting07.c \
raycasting08.c \
raycasting09.c \
render.c \
render_assets_bonus00.c \
render_assets_bonus01.c \
render_assets_bonus02.c \
render_assets_bonus03.c \
render_assets_bonus04.c \
render_assets_bonus05.c \
render_assets_bonus06.c \
render_assets_bonus07.c \
render_assets_bonus08.c \
render_assets_bonus09.c \
render_assets_bonus10.c \
render_assets_bonus11.c \
render_assets_bonus12.c \
render_assets_bonus13.c \
render_assets_bonus14.c \
render_bonus00.c \
render_bonus01.c \
render_bonus02.c \
render_bonus03.c \
render_bonus04.c \
render_floor_bonus.c \
render_sky_floor.c \
render_sky_bonus00.c \
render_sky_bonus01.c \
render_walls00.c \
render_walls01.c \
render_ui_bonus00.c \
render_ui_bonus01.c \
render_ui_bonus02.c \
render_ui_bonus03.c \
render_ui_bonus04.c \
render_ui_bonus05.c \
terminate01.c \
terminate02.c \
terminate03.c \
terminate04.c \
terminate05.c \
textures_load00.c \
textures_load_bonus00.c \
textures_load_bonus01.c \
textures_load_bonus02.c \
textures_load_bonus03.c \
textures_load_bonus04.c \

SHARED_SRCS := $(SHARED_SRCS:%=$(SRC_DIR)/%)

OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(MAIN:.c=.o)) $(AUDIO_DUMMY_SRCS:%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(BONUS_MAIN:.c=.o)) $(AUDIO_DUMMY_SRCS:%.c=$(OBJ_DIR)/%.o)
HELLDIVER_OBJS = $(SHARED_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) $(OBJ_DIR)/$(notdir $(HELLDIVER_MAIN:.c=.o)) $(AUDIO_BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)


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

helldivers3d: $(LIBFT) $(MLX_LIB) copy_libs $(HELLDIVER_NAME)

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
	$(CC) $(CFLAGS) -DHELLDIVER $(HELLDIVER_OBJS) -o $@ -L$(LIBFT_DIR) -lft $(MLX_FLAGS) $(AUDIOFLAGS) -L$(AUDIO_LIB_DIR) -Wl,-rpath,$(AUDIO_LIB_DIR) -include $(SRC_DIR)/cube3d.h -include $(SRC_DIR)/cube3d_bonus.h -include $(SRC_DIR)/cube3d_audio_bonus00.h

copy_libs:
	@mkdir -p $(AUDIO_LIB_DIR)
	@cp /usr/lib/x86_64-linux-gnu/libopenal.so.1 $(AUDIO_LIB_DIR)/ || true
	@cp /usr/lib/x86_64-linux-gnu/libmpg123.so.0 $(AUDIO_LIB_DIR)/ || true

clean:
	rm -f $(OBJ_DIR)/*.o
	@$(MAKE) -C $(MLX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

fcleanhelldivers3d: clean
	rm -f $(NAME) $(BONUS_NAME) $(HELLDIVER_NAME)
	rm -rf $(AUDIO_LIB_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
