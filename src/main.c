/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/17 17:35:54 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int *texture[10]; // Array of pointers for 10 textures

// unsigned int texture[10][64 * 64];  // Example texture array for 10 textures, each 64x64 pixels
unsigned int buffer[DEFAULT_S_HEIGHT][DEFAULT_S_WIDTH]; // Screen buffer for the pixels
void *mlx;
void *win;

unsigned int *load_texture(char *file, int *width, int *height)
{
    void *img;
    int bpp, sl, endian;
    unsigned int *data;

    img = mlx_xpm_file_to_image(mlx, file, width, height);
    if (!img)
    {
        fprintf(stderr, "Error loading %s\n", file);
        exit(1);
    }
    data = (unsigned int *)mlx_get_data_addr(img, &bpp, &sl, &endian);
    // Optionally, you can copy the data to a new buffer if you need to manage multiple textures.
    return data;
}

int charToEnum(char c)
{
    if (c == '0')
        return Empty;
    else if (c == '1')
        return Wall;
    else if (c == 'N')
        return PlayerN;
    else if (c == 'S')
        return PlayerS;
    else if (c == 'E')
        return PlayerE;
    else if (c == 'W')
        return PlayerW;
    else
        return Empty; // Default case to handle unexpected characters or treat them as empty spaces
}

void create_static_map(t_game *game)
{
    // Allocate memory for the map structure
    t_map *map = malloc(sizeof(t_map));
    if (map == NULL)
    {
        fprintf(stderr, "Memory allocation failed for map structure.\n");
        exit(1);
    }
    printf("Allocated memory for the map structure\n");
    // Set the dimensions
    map->width = 24;
    map->height = 24;
    // map->width = game->screen_width;
    // map->height = game->screen_height;
    printf("Set the dimensions\n");

    // Allocate memory for the map data
    map->data = malloc(game->screen_height * sizeof(int *));
    if (map->data == NULL)
    {
        fprintf(stderr, "Memory allocation failed for map data.\n");
        free(map); // Clean up previously allocated map
        exit(1);
    }
    printf("Allocated memory for the map data\n");

    for (int i = 0; i < game->screen_height; i++)
    {
        map->data[i] = malloc(game->screen_width * sizeof(int));
        if (map->data[i] == NULL)
        {
            fprintf(stderr, "Memory allocation failed for map row.\n");
            // Clean up previously allocated rows and map structure
            for (int j = 0; j < i; j++)
            {
                free(map->data[j]);
            }
            free(map->data);
            free(map);
            exit(1);
        }
    }

    // Static map data to copy into the newly allocated map
    int staticMap[24][24] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    // 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    // 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
    // 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    // 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    // };
    printf("defined static map data\n");

    // Copy the static map to the allocated map
    for (int y = 0; y < 24; y++)
    {
        // printf("for (int y = %d; y < screenHeight; y++)\n", y);
        for (int x = 0; x < 24; x++)
        {
            // printf("for int x = %d; x < screenWidth; x++\n", x);
            map->data[y][x] = staticMap[y][x];
        }
    }
    printf("copied the static map to the allocated map\n");

    // Link the map to the game structure
    game->map = map;
}

// int     render_game(t_game *game)
// {
//     // set_up_display(game);

// }

int map_is_valid()
{
    return (1);
}

int create_game_struct(t_game **game)
{
    *game = calloc(1, sizeof(t_game));
    if (*game == NULL)
        return -1;
    (*game)->screen_height = DEFAULT_S_HEIGHT;
    (*game)->screen_width = DEFAULT_S_WIDTH;
    return 0;
}

int create_map(t_game *game)
{
    // Implement map creation and initialization
    create_static_map(game);
    return 0;
}

int create_player(t_game *game)
{
    // Allocate memory for the player structure
    t_player *player = malloc(sizeof(t_player));
    if (player == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the player.\n");
        exit(1); // or handle the error as appropriate
    }

    // Initialize player position
    player->position.x = 22; // Middle of the map, adjust as necessary
    player->position.y = 12;

    // Initialize player direction (looking along the negative x-axis)
    player->direction.x = -1.0f;
    player->direction.y = 0.0f;

    // Initialize the camera plane for the raycasting (related to the FOV)
    player->plane.x = 0.0f;  // Adjust this value to change the FOV
    player->plane.y = 0.66f; // This setting assumes a 66 degrees FOV

    // Initialize pitch (not needed for basic raycasting, useful for up/down look)
    player->pitch = 0.0f;

    // Assign the player to the game structure
    game->player = player;
    return 0;
}

// int set_up_hooks(t_game *game) {
//     // Setup necessary hooks for the game engine
//     return 0;
// }

t_ray_node *calculate_rays(t_game *game, t_ray_node *list)
{
    int x;
    t_ray_node *current;

    current = list;
    x = 0;
    while (x < game->screen_width)
    {
        current = addRay(&list);
        if (current != NULL)
        {
            current->ray.x = x;
            calc_camera_x(game, current);
            calc_ray_dir_x(game, current);
            calc_ray_dir_y(game, current);
            calc_map_x(game, current);
            calc_map_y(game, current);
            calc_side_dist(game, current);
            calc_delta_dist(game, current);
            perform_dda(game, current);
            calc_perp_wall_dist(game, current);
            calc_wall_hit(game, current);
            calc_texture_x(game, current);
            calc_line_height(game, current);
            calc_draw_parameters(game, current);
            // calc_tile_color(game, current);
        }
        x++;
    }
    return (list);
}

void renderFloorAndCeiling(void *mlx, void *win, int screenHeight, int screenWidth)
{
    printf("renderFloorAndCeiling START\n");
    uint32_t floorColor = 0x8B4513;
    uint32_t ceilingColor = 0x87CEEB;

    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; ++x)
        {
            if (y < screenHeight / 2)
            {
                // Apply the ceiling color to the top half of the screen
                // buffer[y][x] = ceilingColor;

                mlx_pixel_put(mlx, win, x, y, ceilingColor);
            }
            else
            {
                // Apply the floor color to the bottom half of the screen
                // buffer[y][x] = floorColor;
                mlx_pixel_put(mlx, win, x, y, floorColor);
            }
        }
    }
    printf("renderFloorAndCeiling END\n");
}

// void    render_floor_and_ceiling()
// {

//     int texWidth, texHeight;
//     // unsigned int *textureData;

//     float dirX = 1.0, dirY = 0.0;  // Example player direction
//     float planeX = 0.0, planeY = 0.66; // Camera plane vector
//     float posX = 22.0, posY = 12.5; // Example player position

//     // Initialize MiniLibX and create a window
//     mlx = mlx_init();
//     win = mlx_new_window(mlx, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Floor Casting Example");

//     // Load the texture
//     // textureData = load_texture("path/to/your/texture.xpm", &texWidth, &texHeight);

//     // You might want to store this texture data in a globally accessible way
//     // or modify your rendering functions to accept dynamic texture arrays.
//     // texture[0] = textureData; // Assuming you have a way to handle this
//     texture[0] = load_texture("textures/wood.xpm", &texWidth, &texHeight);

//     // Call the rendering function
//     renderFloorAndCeiling(DEFAULT_S_HEIGHT, DEFAULT_S_WIDTH, dirX, dirY, planeX, planeY, posX, posY, texWidth, texHeight);

//     // Add a loop to keep the window open and handle events, etc.
//     mlx_loop(mlx);
// }
void render_floor_and_ceiling(t_game *game)
{
    // void *mlx = mlx_init();
    // if (mlx == NULL) {
    //     fprintf(stderr, "Error initializing MiniLibX.\n");
    //     return ;
    // }
    // void *win = mlx_new_window(mlx, DEFAULT_S_WIDTH, DEFAULT_S_HEIGHT, "Simple Floor Ceiling");
    // if (win == NULL) {
    //     fprintf(stderr, "Error creating new window.\n");
    //     return ;
    // }

    // Call the rendering function
    renderFloorAndCeiling(game->mlx_ptr, game->win_ptr, DEFAULT_S_HEIGHT, DEFAULT_S_WIDTH);

    // MiniLibX main loop to handle events
    // mlx_loop(mlx);
    return;
}

void refresh_screenv1(t_game *game)
{
    t_ray_node *list = NULL;

    // floor

    // ceiling
    // render_floor_and_ceiling(game);
    (void)list;

    // walls part
    list = calculate_rays(game, list);
    // render_ray_list(list, game);
}

void refresh_screen(t_game *game)
{
    t_ray_node *list = NULL;

    // floor

    // ceiling
    (void)list;

    // walls part
    list = calculate_rays(game, list);
}

// int render_gamev1(t_game *game)
// {
//     // game->mlx_ptr = mlx_init();
//     // game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
//     refresh_screen(game);
//     set_up_hooks(game);
//     mlx_loop(game->mlx_ptr);
//     return 0;
// }

int initgame(t_game **game)
{
    printf("initgame\n");
    create_game_struct(game);
    create_map(*game);
    create_player(*game);
    setup_game_mlx(*game);

    return (1);
}

int main()
{
    t_game *game;

    game = NULL;
    // if (map_is_valid)
    initgame(&game);

    // test_keyhold();

    (void)game;
    return (0);
}