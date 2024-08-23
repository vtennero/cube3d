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
	// map->width = ((game->cub_map_col_count + 1) / 2);
	// map->height = game->cub_map_row_count;
	map->width = ((game->cub_map_col_count + 1) / 2);
	map->height = game->cub_map_row_count;
    printf("Set the dimensions of width = %d and height = %d\n",map->width,map->height);

    // Allocate memory for the map data
	// map->data = malloc(map->height * sizeof(int *));
    // if (map->data == NULL)
    // {
    //     fprintf(stderr, "Memory allocation failed for map data.\n");
    //     free(map); // Clean up previously allocated map
    //     exit(1);
    // }
    printf("Allocated memory for the map data\n");

   
    map->data = game->cub_map_array;
    if (map->data == NULL)
    {
        fprintf(stderr, "Memory allocation failed for map data.\n");
        free(map); // Clean up previously allocated map
        exit(1);
    }
    printf("Allocated memory for the map data\n");


    // Static map data to copy into the newly allocated map

    // Link the map to the game structure
    game->map = map;
}
int	create_game_struct(t_game **game)
{
	printf("initializing gamestruct\n");
	*game = calloc(1, sizeof(t_game));
	if (*game == NULL)
		return (-1);
	(*game)->screen_height = DEFAULT_S_HEIGHT;
	(*game)->screen_width = DEFAULT_S_WIDTH;
	(*game)->ray_list = NULL;
	(*game)->game_sequence = 3;
	(*game)->current_frame = 0;
	(*game)->loop_count = 0;
	(*game)->is_shooting = 0;
	(*game)->current_shooting_frame = 0;
	(*game)->current_gun_frame = 0;
	(*game)->is_moving_fwd = 0;
	printf("screen_height: %d\n", (*game)->screen_height);
    printf("screen_width: %d\n", (*game)->screen_width);
	printf("initialized gamestruct\n");
	return (0);
}


int	create_map(t_game *game)
{
	// Implement map creation and initialization
	printf("initializing map\n");
	// create_static_map(game);
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





// int create_map(t_game *game)
// {
// 	    create_map_from_cub(game, game->screen_width, game->screen_width);

// }


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

	// player->position.x = 10;
	// player->position.y = 11;
	// Initialize player direction (looking along the negative x-axis)
	// if (game->cub_player_o==2 || game->cub_player_o==4)
	// {
	// 	player->direction.x = 0.0f;
	// 	if (game->cub_player_o==2) 
	// 		player->direction.y = -1.0f;
	// 	else if (game->cub_player_o==4) 
	// 		player->direction.y = 1.0f;
	// }
	// else if (game->cub_player_o==3 || game->cub_player_o==5)
	// {
	// 	player->direction.y = 0.0f;
	// 	if (game->cub_player_o==3) 
	// 		player->direction.x = 1.0f;
	// 	if (game->cub_player_o==5) 
	// 		player->direction.y = -1.0f;
	// }

	// West
	player->direction.x = -1.0f;
	player->direction.y = 0.0f;

	// player->direction.x = 1.0f;
	// player->direction.y = 0.0f;

	// Initialize the camera plane for the raycasting (related to the FOV)
	// player->plane.x = 0.0f;  // Adjust this value to change the FOV
	// player->plane.y = 0.66f; // This setting assumes a 66 degrees FOV
player->plane.x = 0.0f;
player->plane.y = -0.66f;  // Note the negative sign


	// Initialize pitch (not needed for basic raycasting,
		// useful for up/down look)
	player->height = 0.2;
	player->pitch = 0.0f;
	// player->pitch = 0;
	// Assign the player to the game structure
	game->player = player;
	printf("initialized player\n");
	return (0);
}

int	create_collectibles(t_game *game)
{
	printf("initializing collectibles\n");
	game->num_collectibles = 1;
	game->collectibles[0].position.x = 20.5f;
	game->collectibles[0].position.y = 11.5f;
	game->collectibles[0].collected = 0;
	printf("initialized collectibles\n");
	return (0);
}

int	create_extraction(t_game *game)
{
	printf("initializing extrction\n");
	game->extract[0].position.x = 10.5f;
	game->extract[0].position.y = 11.5f;
	game->extract[0].is_activated = 0;
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

int create_enemies(t_game *game)
{
	printf("initializing enemies\n");
    int i;
    // float y_positions[] = {13.0f, 14.0f, 15.0f, 16.0f, 17.0f};

    game->num_enemies = MAX_ENEMIES;

    for (i = 0; i < MAX_ENEMIES; i++)
    {
        // game->enemies[i].position.x = 19.0f;
        // game->enemies[i].position.y = y_positions[i];
        game->enemies[i].is_alive = 1;
        game->enemies[i].frame_count = 0;
        game->enemies[i].current_frame = 0;
        game->enemies[i].momentum = 0;
        game->enemies[i].animation_steps = 0;
    }
	printf("initialized enemies\n");
	randomize_enemy_positions(game);
	printf("randomized enemies\n");
    return (0);
}