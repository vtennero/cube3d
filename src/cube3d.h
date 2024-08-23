/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:31:04 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 17:33:18 by vitenner         ###   ########.fr       */
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
# define MAX_KEY_CODE 65600 // Assuming 65363 is the highest keycode you have
# define TEXTURE_SIZE 245
#define NUM_ENEMY_TEXTURES 14
#define MAX_COLLECTIBLES 20
#define MAX_SUPPLIES 200
#define MAX_ENEMIES 200

#define MAX_WALL_TEXTURES 4
#define MAX_FLOOR_TEXTURES 8
#define MAX_ENEMY_TEXTURES 14
#define MAX_COLLECTIBLE_TEXTURES 1
#define MAX_SHOOTING_TEXTURES 4
#define MAX_SKY_TEXTURES 1
# define MAX_OPENING_TEXTURES 141
# define MAX_LAND_TEXTURES 46
#define FRAMES_PER_SECOND 20
#define MICROSECONDS_PER_FRAME (1000000 / FRAMES_PER_SECOND)
#define MAX_SCRIPTS 500
#define OBJECT_SIZE 1
#define MAX_HEALTH 30
#define MAX_OUTRO_TEXTURES 79

#define M_PI 3.14159265358979323846


/*
** ================== STRUCTURES ==================
*/

typedef struct s_game t_game;

// Now we can use t_game in the ScriptFunction typedef
typedef void (*ScriptFunction)(t_game *game);

typedef struct s_script {
    struct timeval trigger_time;
    ScriptFunction func;
    int is_active;
} t_script;

typedef struct s_script_manager {
    t_script scripts[MAX_SCRIPTS];
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
	Empty = 0,   // Representing '0'
	Wall = 1,    // Representing '1'
	PlayerN = 2, // Representing 'N'
	PlayerS = 3, // Representing 'S'
	PlayerE = 4, // Representing 'E'
	PlayerW = 5  // Representing 'W'
}						MapEntity;

typedef enum e_tiletype
{
	TILE_SPACE = 0,
	TILE_WALL = 1,
	TILE_PLAYER_NORTH = 'N',
	TILE_PLAYER_EAST = 'E',
	TILE_PLAYER_SOUTH = 'S',
	TILE_PLAYER_WEST = 'W',
	// Add more as needed
}						t_tiletype;



typedef struct s_texture
{
	char				*path;
	void				*img;
	char *data; // Pixel data
	int width, height;
	int					tex_bpp;
	int					tex_line_len;
	int					tex_endian;
}						t_texture;



typedef struct s_extract
{
    t_vector2d position;
    int is_available;
    int is_landing;
    int is_activated;
    int is_complete;
    t_vector2d initial_position;
    float delta_time;  // Time passed since last frame
    float landing_progress;  // Time passed since last frame
} t_extract;

typedef struct s_collectible
{
    t_vector2d position;
    int collected;  // 0 for not collected, 1 for collected
    int found;  // 0 for not collected, 1 for collected
} t_collectible;

typedef struct s_supplies
{
    t_vector2d position;
    int collected;  // 0 for not collected, 1 for collected
    int found;  // 0 for not collected, 1 for collected
} t_supplies;

typedef struct s_enemy
{
    t_vector2d position;
    int frame_count;     // for animation timing
    int current_frame;   // current animation frame (0-13)
    int momentum;        // for frame transition (-3 to +3)
    int animation_steps; // count of animation steps for periodic jumps
    int is_alive;        // 0 for dead, 1 for alive
} t_enemy;


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
	int hit;  // was there a wall hit?
	int side; // was a NS or a EW wall hit?
	int					lineHeight;
	int					draw_start;
	int					draw_end;
	int					wall_face;
	int					color;
	int texX;     // Texture X coordinate
	int texY;     // New: Texture Y coordinate for vertical texture mapping
	double wallX; // Exact horizontal position on the wall where the ray hits
}						t_ray;

typedef struct s_ray_node
{
	t_ray				ray;
	struct s_ray_node	*next;
}						t_ray_node;




typedef struct s_game
{
	t_script_manager script_manager;
	void				*mlx_ptr;
	void				*win_ptr;
	t_player			*player;
	t_map				*map;
	t_texture 			walltextures[MAX_WALL_TEXTURES]; // Textures for NORTH, EAST, SOUTH, WEST
	t_texture			floortextures[MAX_FLOOR_TEXTURES];
	t_texture			skytexture[MAX_SKY_TEXTURES];
	t_texture			enemy_textures[MAX_ENEMY_TEXTURES];
	t_texture			coll_texture[MAX_COLLECTIBLE_TEXTURES];
	t_texture			menu_texture[1];
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
    int                 num_collectibles;  // Current number of active collectibles
    int                 num_supplies;  // Current number of active collectibles
    t_enemy             enemies[MAX_ENEMIES];
    int                 num_enemies;  // Current number of active enemies
	int					game_sequence;
	int					current_frame;
	t_texture			land_texture[MAX_LAND_TEXTURES];
	t_extract			extract[1];
	t_texture			extract_texture[2];
	t_texture			supplies_texture[1];
	t_texture			opening_texture[MAX_OPENING_TEXTURES];
	t_texture			outro_texture[MAX_OUTRO_TEXTURES];
	t_texture			shooting_texture[MAX_SHOOTING_TEXTURES];
	struct timeval		opening_start_time;
	int					loop_count;
	int					is_shooting;
	int					is_moving_fwd;
}						t_game;


typedef enum
{
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

/*
** -- MEMORY --
*/
/*
** :: HEADING 3 ::
*/

/*
** ================== INITIALIZATION ==================
*/

// void initgame(t_game *game);

// init
void					initialize_game(t_game *game, int screen_width,
							int screen_height, char *title);
void					preload_textures(t_game *game);
// raycasting

// debug
void					print_map(t_map *map);
void					print_player(const t_player *player);
void					print_ray(const t_ray *ray);
void					print_vector2d(const t_vector2d *vector);
void					printRayList(t_ray_node *head);
t_ray_node				*addRay(t_ray_node **head);

// temp
void					lodev(void);
int						mlx_basic_setup(void);

void					print_ray(const t_ray *ray);

void					calc_camera_x(t_game *game, t_ray_node *ray);

void					calc_ray_dir_x(t_game *game, t_ray_node *ray);

void					calc_ray_dir_y(t_game *game, t_ray_node *ray);

void					calc_map_x(t_game *game, t_ray_node *ray);

void					calc_map_y(t_game *game, t_ray_node *ray);

void					calc_side_dist(t_game *game, t_ray_node *ray);

void					calc_delta_dist(t_game *game, t_ray_node *ray);

void					perform_dda(t_game *game, t_ray_node *ray);

void					calc_perp_wall_dist(t_game *game, t_ray_node *ray);

void					calc_line_height(t_game *game, t_ray_node *ray);

void					calc_draw_parameters(t_game *game, t_ray_node *ray);
// void calc_tile_color(t_game *game, t_ray_node *ray);
void					set_up_hooks(t_game *game);

void					refresh_screen(t_game *game);
void					handle_key_w(t_game *game);
void					handle_key_a(t_game *game);
void					handle_key_s(t_game *game);
void					handle_key_d(t_game *game);
void					handle_key_left(t_game *game);
void					handle_key_right(t_game *game);
void					handle_key_down(t_game *game);
void					handle_key_up(t_game *game);

void					set_texture(t_game *game, t_direction dir);

void					print_game_map(t_game *game);

int						setup_game_mlx(t_game *game);

t_ray_node				*calculate_rays(t_game *game, t_ray_node *list);

int						test_keyhold(void);
int						ft_key_press(int keycode, t_game *game);
int						ft_key_release(int keycode, t_game *game);

void					handle_movement_left(t_game *game);
void					handle_movement_right(t_game *game);
void					handle_movement_up(t_game *game);
void					handle_movement_down(t_game *game);
void					handle_movement_forward(t_game *game);
void					handle_movement_backward(t_game *game);
void					handle_movement_strafe_left(t_game *game);
void					handle_movement_strafe_right(t_game *game);
void					handle_movement_dash(t_game *game);

void					debug_print_rays(t_ray_node *head);

void					calc_texture_x(t_game *game, t_ray_node *ray);
void					calc_wall_hit(t_game *game, t_ray_node *ray);

void					render_floor(t_game *game);
void					img_pix_put(t_img *img, int x, int y, int color);
int						get_texture_color(t_texture *texture, int x, int y);

void					render_floor_pixel(t_game *game, int x, int y,
							float floorX, float floorY);
void					initialize_floor_texture_map(t_game *game);
int						random_int(t_game *game, int max);
unsigned long long		next_random(t_game *game);
void					initialize_game_seed(t_game *game);
void					initialize_floor_texture_weights(t_game *game);
int						select_weighted_texture(t_game *game);
// void render_ray(t_img *img, t_ray ray, t_texture *texture);
void					render_sky(t_game *game, char *sky_texture_path);
void					render_ray_list(t_game *game);
int						render(t_game *game);
void					create_static_map(t_game *game);
int						create_game_struct(t_game **game);
int						create_map(t_game *game);
int						create_player(t_game *game);
void					render_gun(t_game *game);
void					scale_gun_texture(t_game *game);
void					update_gun_state(t_game *game);
void					load_gun_textures(t_game *game, char *path_format,
							int num_frames);
void					scale_gun_textures(t_game *game);
void					scale_shooting_textures(t_game *game);

void					debug_texture(t_texture *texture, int x, int y);

int						handle_mouse_move(int x, int y, t_game *game);

const char				*get_cardinal_direction(float x, float y);


void render_objects(t_game *game);
void render_collectibles(t_game *game);
int	create_collectibles(t_game *game);
void handle_key_e(t_game *game);

void render_enemies(t_game *game);
int create_enemies(t_game *game);
void stopAudio();
void relocate_enemies(t_game *game);
unsigned long long xorshift64(unsigned long long *state);
void handle_key_esc(t_game *game);
void handle_cross_key(t_game *game);
void	cleanup(t_game *game);
void	clean_rays(t_game *game);


// menu
void render_menu(t_game *game);
void handle_key_enter(t_game *game);

// opening
void render_opening(t_game *game);
// int should_increment_frame(struct timeval *start_time);
int get_current_frame(struct timeval *start_time);
void    reset_game_start_time(t_game *game);
long get_elapsed_microseconds(struct timeval *start, struct timeval *end);

void render_land(t_game *game);

// audio
int initializeAudio();
void cleanupAudio();
int playAudioFileWithDelay(const char* filename, float delayInSeconds);
int stopAudioFile(const char* filename);

// extract
int	create_extraction(t_game *game);
void render_extract(t_game *game);


// collectibles
void draw_sprite_stripe(t_game *game, t_texture *collectible_texture, int stripe, int drawStartY, int drawEndY, int spriteHeight, int spriteWidth, int spriteScreenX, float transformY);
t_ray_node* find_ray_node(t_game *game, int stripe);
int is_sprite_in_front(float transformY, int stripe, int screen_width);
void calculate_sprite_width(t_game *game, float transformY, int spriteScreenX, int *spriteWidth, int *drawStartX, int *drawEndX);
void calculate_sprite_height(t_game *game, float transformY, int *spriteHeight, int *drawStartY, int *drawEndY);
int calculate_sprite_screen_x(t_game *game, float transformX, float transformY);
void transform_sprite(t_game *game, float spriteX, float spriteY, float *transformX, float *transformY);
void calculate_sprite_position(t_game *game, float collectibleX, float collectibleY, float *spriteX, float *spriteY);
int get_pixel_color(int x, int y, int width, int height, char *data, int bpp, int line_len);
void c_render_ray_list(t_game *game);

// shoot
int handle_mouse_click(int button, int x, int y, void *param);
int handle_mouse_release(int button, int x, int y, void *param);
void check_enemy_at_center(t_game *game);
int randomize_dead_enemy_positions(t_game *game);
void handle_space_shoot(t_game *game);


// scripts
void testscript(t_game *game);
void add_script(t_game *game, ScriptFunction func, int delay_seconds);
void update_scripts(t_game *game);
int is_player_close_to_collectible(t_game *game);
void    script_found_sth(t_game *game);
void play_gun_sound(t_game *game);
void    trigger_gunshots(t_game *game);
void    get_hit(t_game *game);

// debug
void print_alive_enemies(t_game *game);

int calculate_enemy_count(t_game *game);

void trigger_landing(t_game *game);
int is_player_close_to_extract(t_game *game);
void    script_board(t_game *game);
void trigger_extract_music(t_game *game);
void    sample_acquired(t_game *game);
void    menu_background(t_game *game);
void    menu_background_voice(t_game *game);

// objects
void transform_sprite(t_game *game, float spriteX, float spriteY, float *transformX, float *transformY);
void draw_sprite_stripe(t_game *game, t_texture *obj_texture, int stripe, int drawStartY, int drawEndY, int spriteHeight, int spriteWidth, int spriteScreenX, float transformY);
void calculate_sprite_height(t_game *game, float transformY, int *spriteHeight, int *drawStartY, int *drawEndY);
t_ray_node* find_ray_node(t_game *game, int stripe);
int is_sprite_in_front(float transformY, int stripe, int screen_width);
void calculate_sprite_width(t_game *game, float transformY, int spriteScreenX, int *spriteWidth, int *drawStartX, int *drawEndX);
int calculate_sprite_screen_x(t_game *game, float transformX, float transformY);
void calculate_sprite_position(t_game *game, float object_x, float object_y, float *spriteX, float *spriteY);
int get_pixel_color(int x, int y, int width, int height, char *data, int bpp, int line_len);

// enemies hit
void enemies_hit(t_game *game);
void render_hit(t_game *game);


void render_outro(t_game *game);
int get_current_frame_outro(struct timeval *start_time);

// supplies
void render_supplies(t_game *game);
int	create_supplies(t_game *game);

#endif