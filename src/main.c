/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:31 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/15 14:46:44 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
        return Empty;  // Default case to handle unexpected characters or treat them as empty spaces
}

void create_static_map(t_game *game, int screenWidth, int screenHeight)
{
    // Allocate memory for the map structure
    t_map *map = malloc(sizeof(t_map));
    if (map == NULL) {
        fprintf(stderr, "Memory allocation failed for map structure.\n");
        exit(1);
    }
    printf("Allocated memory for the map structure\n");
    // Set the dimensions
    map->width = screenWidth;
    map->height = screenHeight;
    printf("Set the dimensions\n");

    // Allocate memory for the map data
    map->data = malloc(screenHeight * sizeof(int *));
    if (map->data == NULL) {
        fprintf(stderr, "Memory allocation failed for map data.\n");
        free(map); // Clean up previously allocated map
        exit(1);
    }
    printf("Allocated memory for the map data\n");

    for (int i = 0; i < screenHeight; i++) {
        map->data[i] = malloc(screenWidth * sizeof(int));
        if (map->data[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for map row.\n");
            // Clean up previously allocated rows and map structure
            for (int j = 0; j < i; j++) {
                free(map->data[j]);
            }
            free(map->data);
            free(map);
            exit(1);
        }
    }
    
    // Static map data to copy into the newly allocated map
    int staticMap[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    printf("defined static map data\n");

    // Copy the static map to the allocated map
    for (int y = 0; y < 24; y++)
    {
        // printf("for (int y = %d; y < screenHeight; y++)\n", y);
        for (int x = 0; x < 24; x++) {
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

int     map_is_valid()
{
    return (1);
}

int create_game_struct(t_game **game) {
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
    create_static_map(game, game->screen_width, game->screen_width);
    return 0;
}

int create_player(t_game *game) {
    // Allocate memory for the player structure
    t_player *player = malloc(sizeof(t_player));
    if (player == NULL) {
        fprintf(stderr, "Failed to allocate memory for the player.\n");
        exit(1);  // or handle the error as appropriate
    }

    // Initialize player position
    player->position.x = 22;  // Middle of the map, adjust as necessary
    player->position.y = 12;

    // Initialize player direction (looking along the negative x-axis)
    player->direction.x = -1.0f;
    player->direction.y = 0.0f;

    // Initialize the camera plane for the raycasting (related to the FOV)
    player->plane.x = 0.0f;      // Adjust this value to change the FOV
    player->plane.y = 0.66f;     // This setting assumes a 66 degrees FOV

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


t_ray_node*    calculate_rays(t_game *game, t_ray_node* list)
{
    int x;
    t_ray_node* current;

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
            calc_line_height(game, current);
            calc_draw_parameters(game, current);
        }
        x++;
    }
    return (list);
}

void    refresh_screen(t_game *game)
{
    t_ray_node* list = NULL;

    list = calculate_rays(game, list);
    render_ray_list(list, game->mlx_ptr, game->win_ptr);
}

int render_game(t_game *game)
{
    game->mlx_ptr = mlx_init();
    game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
    refresh_screen(game);
    set_up_hooks(game);
    mlx_loop(game->mlx_ptr);
    return 0;
}

int render_game2(t_game *game)
{
    t_ray_node* list = NULL;
    t_ray_node* current;
    int x;

    game->mlx_ptr = mlx_init();
    game->win_ptr = mlx_new_window(game->mlx_ptr, game->screen_width, game->screen_height, "MLX Window");
    set_up_hooks(game);
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
            calc_line_height(game, current);
            calc_draw_parameters(game, current);
            print_ray(&current->ray);
        }
        x++;
    }

    render_ray_list(list, game->mlx_ptr, game->win_ptr);
    mlx_loop(game->mlx_ptr);
    return 0;
}

int     initgame(t_game **game)
{
    create_game_struct(game);
    create_map(*game);
    create_player(*game);
    render_game(*game);
    return(1);
}

int main()
{
    t_game     *game;

    game = NULL;
    // if (map_is_valid)
        initgame(&game);
    // clean_up();

    // lodev();
    (void)game;
    // mlx_basic_setup();
    return (0);
}