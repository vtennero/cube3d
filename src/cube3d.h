/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:47:43 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/17 16:47:29 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H


# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

# define DEFAULT_S_WIDTH 800
# define DEFAULT_S_HEIGHT 600
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MAX_KEY_CODE 65600
# define TEXTURE_SIZE 245
#define NUM_ENEMY_TEXTURES 14
#define MAX_COLLECTIBLES 20
#define MAX_SUPPLIES 200
#define MAX_ENEMIES 200
#define MAX_GUN_TEXTURES 12

#define MAX_WALL_TEXTURES 4
#define MAX_FLOOR_TEXTURES 8
#define MAX_ENEMY_TEXTURES 14
#define MAX_COLLECTIBLE_TEXTURES 1
#define MAX_SHOOTING_TEXTURES 4
# define MAX_OPENING_TEXTURES 141
# define MAX_LAND_TEXTURES 46
#define FRAMES_PER_SECOND 20
#define MICROSECONDS_PER_FRAME (1000000 / FRAMES_PER_SECOND)
#define MAX_SCRIPTS 500
#define OBJECT_SIZE 1
#define MAX_HEALTH 15
#define MAX_OUTRO_TEXTURES 229
#define EXTRACT_CALL_TIME 120
#define MAX_STRIKES 3

#define M_PI 3.14159265358979323846


#define FIXED_POINT_FACTOR 256
#define MAX_DISTANCE 1000000.0f
#define MAX_RENDER_DISTANCE 1000000.0f

#define NUM_AIRSTRIKE_FRAMES 20
#define NUM_NAPALM_FRAMES 15
#define AIRSTRIKE_ANIMATION_INTERVAL 3
#define NUM_ADJACENT_TILES 3
#define TOTAL_STRIKE_TILES 4
#define NUM_TILES 4
#define NUM_EXPLOSIONS 4
#define EXPLOSION_DELAY 30
#define NUM_NAPALM_OFFSETS 37

#define NUM_OFFSETS 13

#define CROSSHAIR_SIZE 40
#define CROSSHAIR_THICKNESS 1
#define CROSSHAIR_GAP 20
#define DOT_RADIUS 2
#define CROSSHAIR_COLOR 0x00FF00

#define STOP_DISTANCE 2.0f
#define HIT_PROBABILITY 5000

#define HEALTH_BAR_HEIGHT 20
#define HEALTH_BAR_MARGIN 10
#define HEALTH_BAR_BORDER 2

#define COLLECTION_DISTANCE 1.0f

#define BARRAGE_CALL_IN_TIME 8
#define BARRAGE_DURATION 30


#define FIRST_LOOP_START 0
#define SECOND_LOOP_START 135
#define SECOND_LOOP_REPETITIONS 40


#define PROGRESS_BAR_WIDTH 30
#define MAX_TASK_NAME_LENGTH 30
#define TOTAL_PREFIX_LENGTH 40

#define MOUSE_ROT_SPEED 0.005
#define MOUSE_PITCH_SPEED 0.001



/*
** ================== STRUCTURES ==================
*/

typedef struct s_game t_game;


typedef void (*ScriptFunction)(t_game *game);

typedef struct s_script {
	struct timeval trigger_time;
	ScriptFunction func;
	int is_active;

} t_script;

typedef struct s_script_manager {
	t_script scripts[MAX_SCRIPTS];
	int active_script_count;
	int script_count;
} t_script_manager;


typedef struct s_vector2d
{
	float x, y;
}						t_vector2d;

typedef struct s_texture_weight
{
	float				weight;
	int					texture_index;
}						t_texture_weight;

typedef enum s_walltype
{
	north,
	east,
	south,
	west,
	empty
}						t_walltype;

typedef enum
{
	Empty = 0,   	Wall = 1,    	PlayerN = 2, 	PlayerS = 3, 	PlayerE = 4, 	PlayerW = 5  }						MapEntity;

typedef enum e_tiletype
{
	TILE_SPACE = 0,
	TILE_WALL = 1,
	TILE_PLAYER_NORTH = 'N',
	TILE_PLAYER_EAST = 'E',
	TILE_PLAYER_SOUTH = 'S',
	TILE_PLAYER_WEST = 'W',
}						t_tiletype;



typedef struct s_texture
{
	char				*path;
	void				*img;
	char *data; 	int width, height;
	int					tex_bpp;
	int					tex_line_len;
	int					tex_endian;
}						t_texture;


typedef struct s_rgb
{
	char				*path;
	int					red;
	int					green;
	int					blue;
	int 				hex_color;
}						t_rgb;


typedef struct s_opening_state {
	int current_loop;
	int second_loop_count;
	int randomized_frames[MAX_OPENING_TEXTURES - SECOND_LOOP_START];
	int randomized_frames_initialized;
} t_opening_state;


typedef struct s_extract
{
	t_vector2d position;
	int is_available;
	int is_landing;
	int is_activated;
	int is_complete;
	t_vector2d initial_position;
	float delta_time;  	float landing_progress;  } t_extract;

typedef struct s_collectible
{
	t_vector2d position;
	int collected;  	int found;  } t_collectible;

typedef struct s_supplies
{
	t_vector2d position;
	int collected;  	int found;  } t_supplies;


typedef struct s_explosion
{
	t_vector2d offset;
} t_explosion;






typedef struct s_strike
{
	t_vector2d	position;
	t_vector2d	base_position;
	int			is_launching;
	int			is_active;
	int			current_frame;
	int			frame_count;
	int			is_animating;
	int delay_frames;
	int delay_duration;
	int frame_counts[NUM_NAPALM_OFFSETS];
	float speed_multipliers[NUM_NAPALM_OFFSETS];
} t_strike;



typedef struct s_enemy
{
	t_vector2d position;
	int frame_count;     	int current_frame;   	int momentum;        	int animation_steps; 	int is_alive;        } t_enemy;

typedef enum e_direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}						t_direction;

typedef enum e_object
{
	SAMPLE,
}						t_object;

typedef struct s_player
{
	t_vector2d			position;
	t_vector2d			direction;
	t_vector2d			plane;
	float				pitch;
	float				height;
	int					hp;
	int					is_hit;
	int					is_dead;
	int					taking_supplies;
	int					is_extracting;
	int					is_burning;
}						t_player;

typedef struct s_map
{
	int					width;
	int					height;
	int					**data;
}						t_map;

typedef struct s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
}						t_img;

typedef struct s_ray
{
	int					x;
	double				cameraX;
	double				rayDirX;
	double				rayDirY;
	int					mapX;
	int					mapY;
	double				sideDistX;
	double				sideDistY;
	double				deltaDistX;
	double				deltaDistY;
	double				perpWallDist;
	int					stepX;
	int					stepY;
	int hit;  	int side; 	int					lineHeight;
	int					draw_start;
	int					draw_end;
	int					wall_face;
	int					color;
	int texX;     	int texY;     	double wallX; }						t_ray;

typedef struct s_ray_node
{
	t_ray				ray;
	struct s_ray_node	*next;
}						t_ray_node;


typedef struct s_health_bar
{
	t_vector2d pos;
	int width;
	int height;
} t_health_bar;






typedef struct s_game
{
	int					text_err;
	int					loading;
	void				*audio;
	t_script_manager	script_manager;
	void				*mlx_ptr;
	void				*win_ptr;
	t_player			*player;
	t_map				*map;
	t_texture 			walltextures[MAX_WALL_TEXTURES]; 	t_texture			floortextures[MAX_FLOOR_TEXTURES];
	t_texture			enemy_textures[MAX_ENEMY_TEXTURES];
	t_texture			coll_texture[MAX_COLLECTIBLE_TEXTURES];
	t_texture			menu_texture[1];
	t_texture			pelican_inside[1];
	int					screen_height;
	int					screen_width;
	int					bonus;
	t_img				img;
	int					key_state[MAX_KEY_CODE];
	unsigned long long	random_seed;
	int					**floor_texture_map;
	t_texture_weight	floor_texture_weights[MAX_FLOOR_TEXTURES];
	int					num_floor_textures;
	t_texture			*gun_textures;
	int					num_gun_frames;
	int					current_gun_frame;
	int					current_shooting_frame;
	t_ray_node			*ray_list;
	t_collectible       collectibles[MAX_COLLECTIBLES];
	t_supplies       	supplies[MAX_SUPPLIES];
	int                 num_collectibles;  	int                 num_supplies;  	t_enemy             enemies[MAX_ENEMIES];
	int                 num_enemies;  	int					game_sequence;
	int					change_seq;
	int					current_frame;
	t_texture			land_texture[MAX_LAND_TEXTURES];
	t_extract			extract[1];
	t_texture			extract_texture[4];
	t_texture			supplies_texture[1];
	t_texture			opening_texture[MAX_OPENING_TEXTURES];
	t_texture			outro_texture[MAX_OUTRO_TEXTURES];
	t_texture			shooting_texture[MAX_SHOOTING_TEXTURES];
	t_texture			airstrike_textures[NUM_AIRSTRIKE_FRAMES];
	t_texture			napalm_textures[NUM_NAPALM_FRAMES];
	t_texture			sky_texture;
	struct timeval		opening_start_time;
	int					loop_count;
	int					is_shooting;
	int					is_moving_fwd;


	t_opening_state		opening_state;

		char *cub_filepath;
	int  cub_fd;

	int  cub_line_count;
	int  cub_map_row_count;
	int  cub_map_col_count;

	int **cub_map_array;
	int cub_player_x;
	int cub_player_y;
	int cub_player_o;


		t_texture floortexture[1];
		t_rgb floor_rgb[1];
	t_rgb sky_rgb[1];

	t_vector2d			crosshair;
	t_vector2d			center_floor_coords;
	t_strike			strike[MAX_STRIKES];
	}						t_game;



typedef enum
{
	K_1 = 49,
	K_2 = 50,
	K_3 = 51,
	K_A = 97,
	K_B = 98,
	K_C = 99,
	K_D = 100,
	K_E = 101,
	K_F = 102,
	K_G = 103,
	K_H = 104,
	K_I = 105,
	K_J = 106,
	K_K = 107,
	K_L = 108,
	K_M = 109,
	K_N = 110,
	K_O = 111,
	K_P = 112,
	K_Q = 113,
	K_R = 114,
	K_S = 115,
	K_T = 116,
	K_U = 117,
	K_V = 118,
	K_W = 119,
	K_X = 120,
	K_Y = 121,
	K_Z = 122,
	K_SHIFT = 65505,
	K_LEFT = 65361,
	K_RIGHT = 65363,
	K_UP = 65362,
	K_DOWN = 65364,
	K_ESC = 65307,
	K_ENTER = 65293,
	K_SPACE = 65513
}						KeyCodes;

typedef void			(*t_key_func)(t_game *);

typedef struct s_keymap
{
	int					keycode;
	t_key_func			func;
}						t_keymap;


// FUNCTION DECLARATIONS START
char	*trim_whitespace(char *str);
const	char	*get_cardinal_direction(float x, float y);
float	calculate_distance(t_vector2d point1, t_vector2d point2);
float	calc_rotation_angle(int dx);
float	calculate_dynamic_buffer(t_player *player, float base_speed);
float	calculate_floor_distance(int p, float player_height);
float	calculate_new_position_x(t_game *game, float dx, float bump_distance);
float	calculate_new_position_y(t_game *game, float dy, float bump_distance);
float	calculate_screen_shake(t_game *game, int current_frame);
float	random_float(t_game *game);
float	vector2d_distance_squared(t_vector2d a, t_vector2d b);
int	**initialize_array(int x, int y);
int	all_paths_set(t_game *game);
int	assign_texture(char **words, char **path, char *texture);
int	assign_textures(t_game *game, char **words);
int	calculate_enemy_count(t_game *game);
int	calculate_frame(long elapsed_microseconds, int max_textures);
int	calculate_supplies(t_game *game);
int	check_collision_at_point(t_game *game, float dirX, float dirY, float t, float buffer);
int	check_invalid_rgb(char *word);
int	check_line(t_game *game, char *line, int *map_start);
int	check_map_boundaries(t_game *game);
int	check_order_in_column(int **array, int col, int row_count, int direction);
int	check_order_in_row(int **array, int row, int col_count, int direction);
int	check_player_position_helper(t_game *game, int i, int j, int *player_found);
int	check_player_postion_and_map_char(t_game *game);
int	count_words_from_array(char **words);
int	create_collectibles(t_game *game);
int	create_enemies(t_game *game);
int	create_extraction(t_game *game);
int	create_game_struct(t_game **game, int is_bonus);
int	create_map(t_game *game);
int	create_player(t_game *game);
int	create_strike(t_game *game);
int	create_supplies(t_game *game);
int	detect_collision(t_game *game, float newX, float newY);
int	floodfill(t_game *game, int **filled_map, int i, int j);
int	ft_isinteger(char *number);
int	get_current_frame(struct timeval *start_time);
int	get_current_frame_outro(struct timeval *start_time);
int	get_last_three_digit_indexes(char *path, int *f, int *s, int *t);
int	get_last_two_digit_indexes(const char *path, int *first_digit, int *second_digit);
int	get_texture_color(t_texture *texture, int x, int y);
int	handle_error(const char *message, int error_code);
int	handle_first_loop(t_game *game);
int	handle_mouse_move(int x, int y, t_game *game);
int	handle_second_loop(t_game *game);
int	initgame(t_game **game);
int	is_player_close_to_collectible(t_game *game);
int	is_player_close_to_extract(t_game *game);
int	is_valid_location(t_game *game, int x, int y);
int	load_floor_textures(t_game *game);
int	load_texture(t_game *game, t_texture *texture, char *path);
int	load_wall_textures(t_game *game);
int	loop_thru_line_in_map_array(t_game *game);
int	normalize_direction(float *dirX, float *dirY, float length);
int	parse_char_to_int(char chars);
int	parse_floor_sky_rgb(t_game *game);
int	parse_line_to_map_array(char *line, t_game *game, int *map_line);
int	parse_map(t_game *game, char *cub_filepath);
int	parse_map_to_array(t_game *game);
int	prepare_second_loop(t_game *game);
int	print_2d_array(t_game *game, int **array_to_print);
int	random_0_to_3(t_game *game);
int	randomize_enemy_positions(t_game *game);
int	randomize_extract_position(t_game *game);
int	randomize_uncollected_supplies(t_game *game);
int	read_cub_texture_and_analyze_map(t_game *game);
int	respawn_player(t_game *game);
int	rgb_to_hex_int(int red, int green, int blue);
int	select_frame_to_render(t_game *game);
int	texture_err_message(t_game *game);
int	texture_error_handling(t_game *game);
int	validate_digits(const char *path, int first, int second, int third);
int	validate_map(int *valid, int **array, int row_count, int col_count);
int	validate_path_format(const char *path, int len, int min_len);
int	apply_bump(t_game *game, float newX, float newY);
int	bonus_game_loop(t_game *game);
int	bonus_game_loop_0(t_game *game);
int	bonus_game_loop_1(t_game *game);
int	bonus_game_loop_2(t_game *game);
int	bonus_game_loop_3(t_game *game);
int	bonus_game_loop_4(t_game *game);
int	calculate_center_pixel_position(float pitch);
int	calculate_sprite_screen_x(t_game *game, float transformX, float transformY);
int	close_hook(t_game *game);
int	core_game_loop(t_game *game);
int	create_game_window(t_game *game);
int	find_available_slot(t_game *game);
int	find_available_source(t_game *game);
int	find_closest_supply(t_game *game);
int	find_supply_on_player_tile(t_game *game);
int	ft_key_press(int keycode, t_game *game);
int	ft_key_release(int keycode, t_game *game);
int	get_floor_texture_color(t_texture *texture, int x, int y);
int	get_min_starting_index(t_strike *strike);
int	get_next_airstrike_frame(t_strike *strike, int offset_index);
int	get_next_barrage_frame(t_strike *strike);
int	get_next_frame(t_enemy *enemy);
int	get_next_napalm_frame(t_strike *strike, int offset_index);
int	get_pixel_color(int x, int y, int width, int height, char *data, int bpp, int line_len);
int	handle_mouse_click(int button, int x, int y, void *param);
int	handle_mouse_release(int button, int x, int y, void *param);
int	init_game_audio_struct(t_game *game);
int	initialize_audio(t_game *game);
int	initialize_mlx(t_game *game);
int	is_close_enough(t_game *game, t_enemy *enemy);
int	is_script_limit_reached(t_game *game);
int	is_sprite_in_front(float transformY, int stripe, int screen_width);
int	load_collectible_texture(t_game *game);
int	load_enemy_textures(t_game *game);
int	load_extract_textures(t_game *game);
int	load_gun_textures(t_game *game);
int	load_land_textures(t_game *game);
int	load_menu_texture(t_game *game);
int	load_napalm_textures(t_game *game);
int	load_opening_textures(t_game *game);
int	load_outro_textures(t_game *game);
int	load_pelican_inside_texture(t_game *game);
int	load_shooting_textures(t_game *game);
int	load_sky_texture(t_game *game);
int	load_strike_textures(t_game *game);
int	load_supplies_texture(t_game *game);
int	main(int argc, char **argv);
int	play_audio_file(t_game *game, const char *filename, float delayInSeconds);
int	print_progress_bar(int bar_width);
int	print_task_name(const char *task_name);
int	random_int(t_game *game, int max);
int	randomize_dead_enemy_positions(t_game *game);
int	render(t_game *game);
int	select_weighted_texture(t_game *game);
int	setup_game_mlx(t_game *game);
int	should_attempt_hit(unsigned long long *enemy_seed);
int	stop_audio_file(t_game *game, const char *filename);
long	get_elapsed_microseconds(struct timeval *start, struct timeval *end);
t_ray_node	*addRay(t_ray_node **head);
t_ray_node	*calculate_rays(t_game *game, t_ray_node *list);
t_script	create_new_script(ScriptFunction func, struct timeval *now, int delay_seconds);
t_texture	*select_gun_texture(t_game *game);
t_vector2d	calculate_floor_coordinates(t_game *game, t_ray_node *center_ray);
t_vector2d	calculate_mouse_delta(t_vector2d current_pos, t_vector2d center);
t_vector2d	calculate_raw_floor_coordinates(t_game *game, float rayDirX, float rayDirY, float rowDistance);
t_vector2d	clamp_coordinates_to_map(t_vector2d coords, t_map *map);
t_vector2d	get_center_tile_coords(t_game *game);
t_vector2d	get_mouse_position(t_game *game);
unsigned	long long next_random(t_game *game);
unsigned	long long xorshift64(unsigned long long *state);
void	barrage_inbound(t_game *game);
void	calculate_tex_values(t_ray *ray, t_texture *texture, t_game *game, double *texPos, double *step);
void	cancel_supply_take(t_game *game);
void	check_and_kill_enemy(t_game *game, int enemy_index, t_vector2d strike_pos, float radius);
void	check_second_loop_end(t_game *game);
void	clean_map(t_game *game);
void	clean_player(t_game *game);
void	clean_rays(t_game *game);
void	cleanup(t_game *game);
void	delay_napalm_hit(t_game *game);
void	delay_strike_hit(t_game *game);
void	draw_extract_stripe(t_game *game, int stripe, int drawStartY,
		int drawEndY, float distance);
void	eagle_bombs(t_game *game);
void	eagle_inbound(t_game *game);
void	free_array(int **array, int x);
void	free_floor_texture_map(t_game *game);
void	free_split_result(char **words);
void	free_texture_arrays(t_game *game);
void	free_wall_texture_map_path(t_game *game);
void	get_hit(t_game *game);
void	handle_key_3(t_game *game);
void	initialize_randomized_frames(t_game *game);
void	load_bonus_textures(t_game *game);
void	load_textures(t_game *game);
void	menu_background(t_game *game);
void	menu_background_voice(t_game *game);
void	napalm_bombs(t_game *game);
void	napalm_inbound(t_game *game);
void	play_audio_on_frame(t_game *game, int frame_to_render);
void	play_barrage_shell(t_game *game);
void	play_bug_death(t_game *game);
void	play_land_voice(t_game *game);
void	play_random_burn_cry(t_game *game);
void	player_burning(t_game *game);
void	player_need_stims(t_game *game);
void	randomize_uncollected_collectibles(t_game *game,
		int *collectibles_repositioned);
void	remove_napalm(t_game *game);
void	render_current_frame(t_game *game, int frame_to_render);
void	render_extract(t_game *game);
void	render_extract_multi_tile(t_game *game, float base_x, float base_y);
void	render_floor_rgb(t_img *img, int color);
void	render_land(t_game *game);
void	render_menu(t_game *game);
void	render_opening(t_game *game);
void	render_outro(t_game *game);
void	render_pelican_inside(t_game *game);
void	render_ray(t_img *img, t_ray ray, t_texture *texture, t_game *game);
void	render_respawn(t_game *game);
void	render_sky_rgb(t_game *game, int color);
void	render_walls(t_game *game);
void	reset_game_start_time(t_game *game);
void	sample_acquired(t_game *game);
void	script_barrage_enemies(t_game *game);
void	script_barrage_player(t_game *game);
void	script_board(t_game *game);
void	script_die(t_game *game);
void	script_found_sth(t_game *game);
void	script_found_supplies(t_game *game);
void	script_napalm_enemies(t_game *game, int strike_no, float radius);
void	script_napalm_player(t_game *game, int strike_no, float radius);
void	script_skip_enter(t_game *game);
void	script_strike_enemies(t_game *game, int strike_no, float radius);
void	script_strike_player(t_game *game);
void	script_take_supplies(t_game *game);
void	script_takeoff(t_game *game);
void	set_player_direction(t_game *game, t_player *player);
void	setup_bonus_assets(t_game *game);
void	setup_bonus_hooks(t_game *game);
void	setup_bonus_scripts(t_game *game);
void	stop_barrage(t_game *game);
void	strike_helper(t_game *game, int i, int *j);
void	texture_access_check(t_game *game, int *error);
void	trigger_gunshots(t_game *game);
void	trigger_supply_take(t_game *game);
void	update_tex_pos(double *texPos, double step);
void	handle_key_1(t_game *game);
void	handle_key_2(t_game *game);
void	add_script(t_game *game, ScriptFunction func, int delay_seconds);
void	add_script_to_manager(t_game *game, t_script *new_script, int slot);
void	adjust_pitch(t_game *game, int dy);
void	apply_reduced_bump(t_game *game, float dx, float dy, float *bump_distance);
void	bump_player(t_game *game, int enemy_index);
void	calc_camera_x(t_game *game, t_ray_node *ray);
void	calc_delta_dist(t_game *game, t_ray_node *ray);
void	calc_draw_parameters(t_game *game, t_ray_node *ray);
void	calc_line_height(t_game *game, t_ray_node *ray);
void	calc_map_x(t_game *game, t_ray_node *ray);
void	calc_map_y(t_game *game, t_ray_node *ray);
void	calc_mouse_delta(int x, int y, int *last_x, int *last_y, int *dx, int *dy);
void	calc_perp_wall_dist(t_game *game, t_ray_node *ray);
void	calc_ray_dir_x(t_game *game, t_ray_node *ray);
void	calc_ray_dir_y(t_game *game, t_ray_node *ray);
void	calc_side_dist(t_game *game, t_ray_node *ray);
void	calc_texture_x(t_game *game, t_ray_node *ray);
void	calc_wall_hit(t_game *game, t_ray_node *ray);
void	calculate_and_print_center_ray(t_game *game, t_ray_node *center_ray);
void	calculate_gun_position(t_game *game, t_texture *gun_texture, int *start_x, int *start_y);
void	calculate_health_bar_dimensions(t_game *game, t_health_bar *bar);
void	calculate_rotation(t_game *game, float angle);
void	calculate_sprite_height(t_game *game, float transformY, int *spriteHeight, int *drawStartY, int *drawEndY);
void	calculate_sprite_position(t_game *game, float object_x, float object_y, float *spriteX, float *spriteY);
void	calculate_sprite_width(t_game *game, float transformY, int spriteScreenX, int *spriteWidth, int *drawStartX, int *drawEndX);
void	calculate_vector(t_game *game, int enemy_index, float *dx, float *dy);
void	center_mouse(t_game *game, t_vector2d center);
void	check_enemy_at_center(t_game *game);
void	check_last_frame(t_game *game, int frame_to_render);
void	check_texture_loaded(t_texture *texture);
void	clean_mlx(t_game *game);
void	cleanup_audio(t_game *game);
void	clear_previous_output(int last_printed_length);
void	create_game_image(t_game *game);
void	dash_player(t_game *game, float speed);
void	destroy_texture(t_game *game, t_texture *texture);
void	destroy_texture_in_array(t_game *game, t_texture *texture);
void	draw_bottom_crosshair(t_game *game, t_vector2d center);
void	draw_crosshair_line(t_game *game, t_vector2d start, t_vector2d end);
void	draw_dot(t_game *game, t_vector2d center);
void	draw_gun_pixel(t_game *game, t_texture *gun_texture, int start_x, int start_y, int x, int y);
void	draw_health_bar_border(t_game *game, t_health_bar *bar);
void	draw_health_bar_fill(t_game *game, t_health_bar *bar);
void	draw_health_bar_leftright(t_game *game, t_health_bar *bar);
void	draw_health_bar_topbottom(t_game *game, t_health_bar *bar);
void	draw_left_crosshair(t_game *game, t_vector2d center);
void	draw_right_crosshair(t_game *game, t_vector2d center);
void	draw_sprite_stripe(t_game *game, t_texture *obj_texture, int stripe, int drawStartY, int drawEndY, int spriteHeight, int spriteWidth, int spriteScreenX, float transformY);
void	draw_strike_stripe(t_game *game, int stripe, int drawStartY, int drawEndY, float distance);
void	draw_top_crosshair(t_game *game, t_vector2d center);
void	enemies_hit(t_game *game);
void	enemy_hit_attempt(t_game *game, t_enemy *enemy, int index);
void	extraction_available(t_game *game);
void	free_gun_texture_frames(t_game *game);
void	free_gun_textures(t_game *game);
void	free_shooting_textures(t_game *game);
void	free_sky_texture(t_game *game);
void	free_texture_array(t_texture *texture_array, int num_items, t_game *game);
void	handle_key_a(t_game *game);
void	handle_key_d(t_game *game);
void	handle_key_down(t_game *game);
void	handle_key_e(t_game *game);
void	handle_key_enter(t_game *game);
void	handle_key_esc(t_game *game);
void	handle_key_left(t_game *game);
void	handle_key_right(t_game *game);
void	handle_key_s(t_game *game);
void	handle_key_up(t_game *game);
void	handle_key_w(t_game *game);
void	handle_movement_backward(t_game *game);
void	handle_movement_dash(t_game *game);
void	handle_movement_down(t_game *game);
void	handle_movement_forward(t_game *game);
void	handle_movement_left(t_game *game);
void	handle_movement_right(t_game *game);
void	handle_movement_strafe_left(t_game *game);
void	handle_movement_strafe_right(t_game *game);
void	handle_movement_up(t_game *game);
void	img_pix_put(t_img *img, int x, int y, int color);
void	init_last_pos(int x, int y, int *last_x, int *last_y);
void	initialize_floor_texture_map(t_game *game);
void	initialize_floor_texture_weights(t_game *game);
void	initialize_game_seed(t_game *game);
void	normalize_vector(float *dx, float *dy);
void	perform_dda(t_game *game, t_ray_node *ray);
void	play_gun_sound(t_game *game);
void	play_random_eagle_call(t_game *game);
void	play_random_strike_sound(t_game *game);
void	randomize_barrage_location(t_game *game);
void	relocate_enemies(t_game *game);
void	relocate_enemy(t_game *game, t_enemy *enemy, int index);
void	render_barrage(t_game *game);
void	render_call_barrage(t_game *game, t_vector2d position);
void	render_call_strike(t_game *game, t_vector2d position);
void	render_collectible(t_game *game, t_vector2d position);
void	render_collectibles(t_game *game);
void	render_crosshair(t_game *game);
void	render_enemies(t_game *game);
void	render_enemy(t_game *game, t_enemy *enemy);
void	render_floor(t_game *game);
void	render_floor_pixel(t_game *game, int x, int y, float floorX, float floorY);
void	render_frame(t_game *game, t_texture *opening_texture);
void	render_gun(t_game *game);
void	render_health_bar(t_game *game);
void	render_hit(t_game *game);
void	render_napalm(t_game *game);
void	render_ongoing_barrage(t_game *game);
void	render_ongoing_napalm(t_game *game);
void	render_ongoing_strike(t_game *game);
void	render_sky(t_game *game);
void	render_strike(t_game *game);
void	render_supplies(t_game *game);
void	render_supply(t_game *game, t_vector2d position);
void	render_supply_take(t_game *game);
void	reset_gun_frames(t_game *game);
void	rotate_player(t_game *game, float angle);
void	rotate_vector(float *x, float *y, float angle);
void	run_raycasting_calculation_1(t_game *game, t_ray_node *current);
void	run_raycasting_calculation_2(t_game *game, t_ray_node *current);
void	run_raycasting_calculation_3(t_game *game, t_ray_node *current);
void	scale_gun_textures(t_game *game);
void	scale_shooting_textures(t_game *game);
void	set_crosshair_position(t_game *game);
void	setup_bonus_features(t_game *game);
void	setup_game_hooks(t_game *game);
void	testscript(t_game *game);
void	transform_sprite(t_game *game, float spriteX, float spriteY, float *transformX, float *transformY);
void	trigger_extract_music(t_game *game);
void	trigger_extract_victory(t_game *game);
void	trigger_landing(t_game *game);
void	trigger_prelanding(t_game *game);
void	update_gun_state(t_game *game);
void	update_normal_gun_frame(t_game *game);
void	update_progress_bar(t_game *game, int current, int total, const char *task_name);
void	update_scripts(t_game *game);
void	update_shooting_gun_frame(t_game *game);

// FUNCTION DECLARATIONS END

#endif
