/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:55:07 by vitenner          #+#    #+#             */
/*   Updated: 2024/05/07 12:04:37 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	create_game_struct(t_game **game)
{
	printf("initializing gamestruct\n");
	*game = calloc(1, sizeof(t_game));
	if (*game == NULL)
		return (-1);
	(*game)->screen_height = DEFAULT_S_HEIGHT;
	(*game)->screen_width = DEFAULT_S_WIDTH;
	(*game)->ray_list = NULL;
	(*game)->game_sequence = 0;
	(*game)->current_frame = 0;
	(*game)->loop_count = 0;
	(*game)->is_shooting = 0;
	(*game)->current_shooting_frame = 0;
	(*game)->current_gun_frame = 0;
	(*game)->is_moving_fwd = 0;
	(*game)->script_manager = (t_script_manager){0};

	printf("screen_height: %d\n", (*game)->screen_height);
    printf("screen_width: %d\n", (*game)->screen_width);
	printf("initialized gamestruct\n");
	return (0);
}

void create_map_from_cub(t_game *game)
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
    // map->width = 24;
    // map->height = 24;
    // map->width = game->screen_width;
    // map->height = game->screen_height;

	map->width = ((game->cub_map_col_count + 1) / 2);
	map->height = game->cub_map_row_count;
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

   
    // Copy the static map to the allocated map
    for (int x = 0; x <map->height ; x++)
    {
        // printf("for (int y = %d; y < screenHeight; y++)\n", y);
        for (int y = 0; y < map->width ; y++)
        {
            // printf("for int x = %d; x < screenWidth; x++\n", x);
            // map->data[y][x] = staticMap[x][y];
            map->data[x][y] =  game->cub_map_array[x][y];
        }
    }
    printf("copied the static map to the allocated map\n");

    // Link the map to the game structure
    game->map = map;
}


int	create_map(t_game *game)
{
	// Implement map creation and initialization
	printf("initializing map\n");
	//create_static_map(game);
	create_map_from_cub(game);

	printf("initialized map\n");
	return (0);
}
	int print_2d_array(t_game *game,int ** array_to_print)
{
	int x;
	int y;
	x =game->cub_map_row_count;
	y=((game->cub_map_col_count + 1) / 2);

	printf("\n GAME MAP ARRAY \n _________________________________ \n");

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
	
            printf("%d ", array_to_print[i][j]);
        }
        printf("\n");
    }
	return 1;
}


int parse_map(t_game *game,char *cub_filepath)
{
	game->cub_filepath=cub_filepath;
	printf("%s",cub_filepath);
	printf("%s",game->cub_filepath);
	if (read_cub_texture_and_analyze_map(game)==-1)
		return -1;
	if (texture_error_handling(game) == -1)
		return -1;
	parse_floor_sky_rgb(game);
	printf("Sky Red is %d,Green is %d, Blue is %d, and hex int is %d",game->sky_rgb[0].red,game->sky_rgb[0].green,game->sky_rgb[0].blue,game->sky_rgb[0].hex_color);
	printf("Floor Red is %d,Green is %d, Blue is %d, and hex int is %d",game->floor_rgb[0].red,game->floor_rgb[0].green,game->floor_rgb[0].blue,game->floor_rgb[0].hex_color);

	printf("\nTotal Cub line count is %d",game->cub_line_count);
	printf("\nTotal Map line count is %d",game->cub_map_row_count);
	printf("\nTotal Map col count is %d",game->cub_map_col_count);
	if (parse_map_to_array(game) == -1)
		return -1;
	if (check_map_boundaries(game) ==-1)
		return -1;
    // Implement map creation and initialization

    return 0;
}


int create_strike(t_game *game)
{
    t_strike *strike = malloc(sizeof(t_strike));
	if (strike == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for the strike.\n");
		exit(1); // or handle the error as appropriate
	}
    strike->position.x = 0;
    strike->position.y = 0;
    strike->is_active = 0;
    strike->is_launching = 0;
    strike->current_frame = 0;
    strike->frame_count = 0;

	game->strike = strike;
	printf("initialized strike\n");
    return (1);
}

int	create_player(t_game *game)
{
	printf("initializing player\n");
	// Allocate memory for the player structure
	t_player *player = malloc(sizeof(t_player));
	if (player == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for the player.\n");
		exit(1); // or handle the error as appropriate
	}


	// Initialize player position
	player->position.x = game->cub_player_y;
	player->position.y = game->cub_player_x;




	// Initialize player direction (looking along the negative x-axis)
	player->direction.x = -1.0f;
	player->direction.y = 0.0f;

	// Initialize the camera plane for the raycasting (related to the FOV)
	// player->plane.x = 0.0f;  // Adjust this value to change the FOV
	// player->plane.y = 0.66f; // This setting assumes a 66 degrees FOV
    player->plane.x = 0.0f;
    player->plane.y = -0.66f;  // Note the negative sign


	// Initialize pitch (not needed for basic raycasting,
		// useful for up/down look)
	// player->height = 0.0f;
	player->height = 0.2;
	player->pitch = 0.0f;
	player->hp = MAX_HEALTH;
	player->is_hit = 0;
	player->taking_supplies = 0;
	// player->pitch = 0;
	// Assign the player to the game structure
	game->player = player;
	printf("initialized player\n");
	return (0);
}

int randomize_extract_position(t_game *game)
{
    int x, y;
    int valid_position = 0;

    while (!valid_position)
    {
        x = random_int(game, game->map->width);
        y = random_int(game, game->map->height);

        // Check if the current position and all adjacent tiles are not walls
        if (game->map->data[y][x] != 1 &&
            (x == 0 || game->map->data[y][x-1] != 1) &&
            (x == game->map->width - 1 || game->map->data[y][x+1] != 1) &&
            (y == 0 || game->map->data[y-1][x] != 1) &&
            (y == game->map->height - 1 || game->map->data[y+1][x] != 1) &&
            (x == 0 || y == 0 || game->map->data[y-1][x-1] != 1) &&
            (x == game->map->width - 1 || y == 0 || game->map->data[y-1][x+1] != 1) &&
            (x == 0 || y == game->map->height - 1 || game->map->data[y+1][x-1] != 1) &&
            (x == game->map->width - 1 || y == game->map->height - 1 || game->map->data[y+1][x+1] != 1))
        {
            valid_position = 1;
        }
    }

    game->extract[0].position.x = (float)x + 0.5f; // Center in the tile
    game->extract[0].position.y = (float)y + 0.5f; // Center in the tile

    return 1; // Return 1 to indicate successful repositioning
}

int randomize_uncollected_collectibles(t_game *game)
{
    int i = 0;
    int x, y;
    int collectibles_repositioned = 0;
    
    while (i < game->num_collectibles)
    {
        if (game->collectibles[i].collected == 0)
        {
            x = random_int(game, game->map->width);
            y = random_int(game, game->map->height);
            
            while (game->map->data[y][x] == 1)
            {
                x = random_int(game, game->map->width);
                y = random_int(game, game->map->height);
            }
            
            game->collectibles[i].position.x = (float)x + 0.5f; // Center in the tile
            game->collectibles[i].position.y = (float)y + 0.5f; // Center in the tile
            game->collectibles[i].collected = 0; // Mark as uncollected
            game->collectibles[i].found = 0; // Mark as not found
            collectibles_repositioned++;
        }
        i++;
    }
    
    return (collectibles_repositioned);
}

// int randomize_uncollected_supplies(t_game *game)
// {
//     int i = 0;
//     int x, y;
//     int supplies_repositioned = 0;
    
//     while (i < game->num_supplies)
//     {
//         if (game->supplies[i].collected == 0)
//         {
//             do {
//                 x = random_int(game, game->map->width);
//                 y = random_int(game, game->map->height);
//             } while (
//                 game->map->data[y][x] == 1 ||
//                 (x == (int)game->extract[0].position.x && y == (int)game->extract[0].position.y) ||
//                 (abs(x - (int)game->extract[0].position.x) <= 1 && abs(y - (int)game->extract[0].position.y) <= 1)
//             );
            
//             game->supplies[i].position.x = (float)x + 0.5f; // Center in the tile
//             game->supplies[i].position.y = (float)y + 0.5f; // Center in the tile
//             game->supplies[i].collected = 0; // Mark as uncollected
//             game->supplies[i].found = 0; // Mark as not found
//             supplies_repositioned++;
//         }
//         i++;
//     }
    
//     return (supplies_repositioned);
// }

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Subfunction to check if a location is valid
int is_valid_location(t_game *game, int x, int y) {
    // Check if the location is within map bounds
    if (x < 0 || x >= game->map->width || y < 0 || y >= game->map->height) {
        return 0;
    }
    
    // Check if the location is not an obstacle
    if (game->map->data[y][x] == 1) {
        return 0;
    }
    
    // Check if the location is not the extraction point or adjacent to it
    int extract_x = (int)game->extract[0].position.x;
    int extract_y = (int)game->extract[0].position.y;
    if (abs(x - extract_x) <= 1 && abs(y - extract_y) <= 1) {
        return 0;
    }
    
    return 1;
}

int randomize_uncollected_supplies(t_game *game)
{
    int supplies_repositioned = 0;
    
    for (int i = 0; i < game->num_supplies; i++) {
        if (game->supplies[i].collected == 0) {
            int x, y;
            int valid_location_found = 0;
            
            while (!valid_location_found) {
                x = random_int(game, game->map->width);
                y = random_int(game, game->map->height);
                
                if (is_valid_location(game, x, y)) {
                    valid_location_found = 1;
                }
            }
            
            game->supplies[i].position.x = (float)x + 0.5f; // Center in the tile
            game->supplies[i].position.y = (float)y + 0.5f; // Center in the tile
            game->supplies[i].collected = 0; // Mark as uncollected
            game->supplies[i].found = 0; // Mark as not found
            supplies_repositioned++;
            
            // Print the valid location found and the extraction location
            printf("Supply placed at (%d, %d). Extraction at (%.1f, %.1f)\n", 
                   x, y, game->extract[0].position.x, game->extract[0].position.y);
        }
    }
    
    return supplies_repositioned;
}


// int randomize_uncollected_supplies(t_game *game)
// {
//     int i = 0;
//     int x, y;
//     int supplies_repositioned = 0;
    
//     while (i < game->num_supplies)
//     {
//         if (game->supplies[i].collected == 0)
//         {
//             x = random_int(game, game->map->width);
//             y = random_int(game, game->map->height);
            
//             while (game->map->data[y][x] == 1)
//             {
//                 x = random_int(game, game->map->width);
//                 y = random_int(game, game->map->height);
//             }
            
//             game->supplies[i].position.x = (float)x + 0.5f; // Center in the tile
//             game->supplies[i].position.y = (float)y + 0.5f; // Center in the tile
//             game->supplies[i].collected = 0; // Mark as uncollected
//             game->supplies[i].found = 0; // Mark as not found
//             supplies_repositioned++;
//         }
//         i++;
//     }
    
//     return (supplies_repositioned);
// }

int	create_collectibles(t_game *game)
{
	printf("initializing collectibles\n");
	game->num_collectibles = 1;
	randomize_uncollected_collectibles(game);
	// game->collectibles[0].position.x = 20.5f;
	// game->collectibles[0].position.y = 11.5f;
	game->collectibles[0].collected = 0;
	game->collectibles[0].found = 0;
	printf("initialized collectibles\n");
	return (0);
}

int	create_extraction(t_game *game)
{
	printf("initializing extraction\n");
	// game->extract[0].position.x = 10.5f;
	// game->extract[0].position.y = 11.5f;
	randomize_extract_position(game);
	game->extract[0].is_activated = 0;
	game->extract[0].is_available = 0;
	game->extract[0].is_landing = 0;
	printf("initialized extraction\n");
	return (0);
}



int randomize_enemy_positions(t_game *game)
{
    printf("Randomizing enemy positions\n");
    int i, x, y;
    
    for (i = 0; i < game->num_enemies; i++)
    {
        do {
            x = random_int(game, game->map->width);
            y = random_int(game, game->map->height);
        } while (game->map->data[y][x] == 1); // Keep trying until we find a non-wall position
        
        game->enemies[i].position.x = (float)x + 0.5f; // Center in the tile
        game->enemies[i].position.y = (float)y + 0.5f; // Center in the tile
    }
    
    printf("Enemy positions randomized\n");
    return (0);
}

int calculate_enemy_count(t_game *game)
{
    int map_area = game->map->width * game->map->height;
    int base_area = 24 * 24;
    int base_count;

    // Determine base count based on game state
    if (game->extract->is_landing) {
        base_count = 20;
    } else if (game->extract->is_activated) {
        base_count = 15;
    } else if (game->collectibles[0].collected) {
        base_count = 5;
    } else {
        base_count = 2;
    }

    // Calculate enemy count proportional to map area
    int enemy_count = (map_area * base_count) / base_area;

    // Ensure the count is within acceptable bounds
    if (enemy_count < 1) {
        enemy_count = 1;
    } else if (enemy_count > MAX_ENEMIES) {
        enemy_count = MAX_ENEMIES;
    }

    return enemy_count;
}

int calculate_supplies(t_game *game)
{
    int map_area = game->map->width * game->map->height;
    int base_area = 24 * 24;
    int base_count = 5;  // Fixed number of supplies for the base area

    // Calculate supply count proportional to map area
    int supply_count = (map_area * base_count) / base_area;

    // Ensure the count is within acceptable bounds
    if (supply_count < 1) {
        supply_count = 1;
    } else if (supply_count > MAX_SUPPLIES) {
        supply_count = MAX_SUPPLIES;
    }

    return supply_count;
}

int create_enemies(t_game *game)
{
	printf("initializing enemies\n");
    int i;
    // float y_positions[] = {13.0f, 14.0f, 15.0f, 16.0f, 17.0f};

    game->num_enemies = calculate_enemy_count(game);
    // game->num_enemies = 5;

    for (i = 0; i < MAX_ENEMIES; i++)
    {
        // game->enemies[i].position.x = 19.0f;
        // game->enemies[i].position.y = y_positions[i];
        game->enemies[i].is_alive = 0;
        game->enemies[i].frame_count = 0;
        game->enemies[i].current_frame = 0;
        game->enemies[i].momentum = 0;
        game->enemies[i].animation_steps = 0;
    }
	for (i = 0; i < game->num_enemies; i++)
    {
        game->enemies[i].is_alive = 1;
    }
	printf("initialized enemies\n");
	randomize_enemy_positions(game);
	printf("randomized enemies\n");
    return (0);
}

int	create_supplies(t_game *game)
{
	printf("initializing supplies\n");
	game->num_supplies = calculate_supplies(game);
    printf("game->num_supplies %d\n", game->num_supplies);
	randomize_uncollected_supplies(game);
	printf("initialized supplies\n");
	return (0);
}