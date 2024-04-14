/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:31:04 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/15 01:33:51 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <fcntl.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define screenWidth 640
#define screenHeight 480

/*
** ================== STRUCTURES ==================
*/
typedef struct s_vector2d{
    float x, y;
} t_vector2d;

typedef enum s_walltype {
    north, east, south, west, empty
} t_walltype;

typedef enum {
    Empty = 0,  // Representing '0'
    Wall = 1,   // Representing '1'
    PlayerN = 2,  // Representing 'N'
    PlayerS = 3,  // Representing 'S'
    PlayerE = 4,  // Representing 'E'
    PlayerW = 5   // Representing 'W'
} MapEntity;

typedef enum e_tiletype {
    TILE_SPACE = 0,
    TILE_WALL = 1,
    TILE_PLAYER_NORTH = 'N',
    TILE_PLAYER_EAST = 'E',
    TILE_PLAYER_SOUTH = 'S',
    TILE_PLAYER_WEST = 'W',
    // Add more as needed
} t_tiletype;


typedef struct s_ray {
    t_vector2d dir;
    float distance;
    t_walltype hitwalltype;
} t_ray;

typedef struct s_texture {
    void* img;
    int width, height;
} t_texture;

typedef struct s_player {
    t_vector2d position;
    t_vector2d direction;
    t_vector2d plane;
    float pitch;
} t_player;

// typedef struct s_map {
//     int width, height;
//     unsigned char** tiles; // Using unsigned char to match our enum
// } t_map;

typedef struct s_map {
    int width;
    int height;
    int **data;
} t_map;


typedef struct s_game {
	void* mlx_ptr;
    void* win_ptr;
    void* img_ptr;
    char* img_data;
    int bits_per_pixel;
    int size_line;
    int endian;
    t_player *player;
    t_map *map;
    t_texture walltextures[4]; // Textures for NORTH, EAST, SOUTH, WEST
    t_texture *floortexture;
    t_texture *ceilingtexture;
	int	bonus;
} t_game;

typedef struct {
    int x;
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
    int hit; // was there a wall hit?
    int side; // was a NS or a EW wall hit?
    int lineHeight;
    int draw_start;
    int draw_end;
    int color;
} t_ray;

typedef struct t_ray_node {
    t_ray ray;
    struct t_ray_node* next;
} t_ray_node;

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
    // Initializes the game, sets up mlx, loads textures, and initializes the player and map.
void loadtexture(void* mlx, t_texture* texture, const char* path);
    // Loads a texture image from the specified path and stores it in the texture structure.
void updateplayerposition(t_game *game, float deltatime);
    // Updates the player's position based on input. Adjusts direction and plane for rotation, handles collisions.
void castray(t_game *game, t_vector2d raydir);
    // Casts a ray into the scene from the player's position in the specified direction and updates the ray structure.
void renderscene(t_game *game);
    // Renders the entire scene, including walls, floor, and ceiling. Adjusts rendering based on player's pitch.
    // Calls drawfloorandceiling and drawwallslice for each ray.
void drawfloorandceiling(t_game *game);
    // Draws the floor and ceiling, adjusting for the player's pitch to correctly position the view.
void drawwallslice(t_game *game, int x, t_ray* ray);
    // Draws a single vertical slice of a wall at screen position x, based on the specified ray's distance and hit wall type.
    // Takes into account the player's pitch for vertical positioning.
void handlemousemovement(t_game *game, int x, int y);
    // Handles mouse movement events. Adjusts the player's direction, plane, and pitch based on mouse position changes.
void mainloop(t_game *game);
    // The main game loop. Handles events, updates the game state, and renders frames.
    // Calls updateplayerposition, renderscene, and potentially handlemousemovement if mouse movement is detected.

// init
void initialize_game(t_game* game, int screen_width, int screen_height, char* title);

// raycasting
// void calculate_rays(t_game *game, int screenWidth);

// debug
void print_map(t_map* map);
// t_map *create_static_map(void);
void list_first_ten_rays(t_ray *rays, int count);
void print_player(const t_player *player);
void print_ray(const t_ray *ray);
void print_vector2d(const t_vector2d *vector);
// void addRay(t_ray_node** head, int x, int draw_start, int draw_end, int color);
void printRayList(t_ray_node* head);
void render_ray_list(t_ray_node* head, void *mlx_ptr, void *win_ptr);
t_ray_node  *addRay(t_ray_node** head);

// temp
void	lodev();
int    mlx_basic_setup();
# endif