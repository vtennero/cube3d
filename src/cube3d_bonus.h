/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:44:51 by toto              #+#    #+#             */
/*   Updated: 2024/09/09 16:15:59 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H_BONUS
# define CUBE3D_H_BONUS


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
#define MAX_SKY_TEXTURES 1
# define MAX_OPENING_TEXTURES 141
# define MAX_LAND_TEXTURES 46
#define FRAMES_PER_SECOND 20
#define MICROSECONDS_PER_FRAME (1000000 / FRAMES_PER_SECOND)
#define MAX_SCRIPTS 500
#define OBJECT_SIZE 1
#define MAX_HEALTH 15
// #define MAX_HEALTH 50
#define MAX_OUTRO_TEXTURES 229
// #define EXTRACT_CALL_TIME 15
#define EXTRACT_CALL_TIME 120
#define MAX_STRIKES 3

#define M_PI 3.14159265358979323846


// floor rendering
#define FIXED_POINT_FACTOR 256
#define MAX_DISTANCE 1000000.0f
#define MAX_RENDER_DISTANCE 1000000.0f

// airstrikes
#define NUM_AIRSTRIKE_FRAMES 20
#define NUM_NAPALM_FRAMES 15
#define AIRSTRIKE_ANIMATION_INTERVAL 3  // Change frame every 3 game ticks
#define NUM_ADJACENT_TILES 3
#define TOTAL_STRIKE_TILES 4 // Including the main tile
#define NUM_TILES 4
#define NUM_EXPLOSIONS 4
#define EXPLOSION_DELAY 30 // Frames between explosion starts
#define NUM_NAPALM_OFFSETS 37

#define NUM_OFFSETS 13

// crosshair
#define CROSSHAIR_SIZE 40
#define CROSSHAIR_THICKNESS 1
#define CROSSHAIR_GAP 20
#define DOT_RADIUS 2
#define CROSSHAIR_COLOR 0x00FF00

// enemy hit logic
#define STOP_DISTANCE 2.0f
#define HIT_PROBABILITY 5000

// GAME INTERFACE
#define HEALTH_BAR_HEIGHT 20
#define HEALTH_BAR_MARGIN 10
#define HEALTH_BAR_BORDER 2

// samples
#define COLLECTION_DISTANCE 1.0f

// barrage
#define BARRAGE_CALL_IN_TIME 8
#define BARRAGE_DURATION 30

// intro

#define FIRST_LOOP_START 0
#define SECOND_LOOP_START 135
#define SECOND_LOOP_REPETITIONS 40


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


// stable
typedef struct s_explosion
{
	t_vector2d offset;
} t_explosion;




// typedef struct s_strike
// {
// 	t_vector2d	position;
// 	int			is_launching;
// 	int			is_active;
//    	int			current_frame[NUM_EXPLOSIONS];
// 	int			frame_count[NUM_EXPLOSIONS];
// } t_strike;


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


typedef struct s_health_bar
{
	t_vector2d pos;
	int width;
	int height;
} t_health_bar;

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
	int                 num_collectibles;  // Current number of active collectibles
	int                 num_supplies;  // Current number of active collectibles
	t_enemy             enemies[MAX_ENEMIES];
	int                 num_enemies;  // Current number of active enemies
	int					game_sequence;
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
	struct timeval		opening_start_time;
	int					loop_count;
	int					is_shooting;
	int					is_moving_fwd;


	t_opening_state		opening_state;

	// Cub parsing
	char *cub_filepath;
	int  cub_fd;

	int  cub_line_count;
	int  cub_map_row_count;
	int  cub_map_col_count;

	int **cub_map_array;
	int cub_player_x;
	int cub_player_y;
	int cub_player_o;


	// t_texture walltextures_[4]; // Textures for NORTH, EAST, SOUTH, WEST
	t_texture floortexture[1];
	// t_texture skytexture[1];
	t_rgb floor_rgb[1];
	t_rgb sky_rgb[1];

    t_vector2d			crosshair;
	t_vector2d			center_floor_coords;
	t_strike			strike[MAX_STRIKES];
	// t_strike			*strike;
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


/*
** ================== INITIALIZATION ==================
*/

/*
** ================== PLAYER ==================
*/

/*
** ================== MOVEMENT ==================
*/


/*
** ================== TEXTURES ==================
*/



/*
** ================== FLOOR ==================
*/

/*
** ================== SKY ==================
*/

/*
** ================== WORLD OBJECTS ==================
*/

/*
** ================== ENEMIES ==================
*/

/*
** ================== COLLECTIBLES ==================
*/

/*
** ================== SUPPLIES ==================
*/

/*
** ================== STRIKES ==================
*/

/*
** ================== SCRIPTS ==================
*/

/*
** ================== SHOOTING ==================
*/

/*
** ================== EXTRACT ==================
*/

/*
** ================== AUDIO ==================
*/

/*
** ================== MENU ==================
*/

/*
** ================== INTRO ==================
*/

/*
** ================== OUTRO ==================
*/

/*
** ================== DEBUG ==================
*/



#endif
