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

int	create_map(t_game *game)
{
	// Implement map creation and initialization
	printf("initializing map\n");
	create_static_map(game);
	printf("initialized map\n");
	return (0);
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
	player->position.x = 22;
	player->position.y = 12;

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
	player->hp = 100;
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
	printf("initializing extrction\n");
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

