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

void initialize_player(t_player *player) {
    // Set initial position (example: middle of the map)
    player->position.x = 12.0f; // Adjust as needed
    player->position.y = 12.0f; // Adjust as needed

    // Set initial direction (looking down the x-axis)
    player->direction.x = -1.0f; // Change depending on initial direction
    player->direction.y = 0.0f;

    // Set the 2D raycaster camera plane, determining the FOV
    // This example assumes a FOV of approximately 66 degrees
    // plane.x is related to the FOV, where tan(FOV/2) = |plane.x|/|dir.x|
    // For dir.x = -1, dir.y = 0, a plane.x = 0.66 gives FOV of 66 degrees
    // player->plane.x = 0.66f;
    // player->plane.y = 0.0f; // Adjust FOV by changing this value

    player->plane.x = 0;
    player->plane.y = 0.66f; // Adjust FOV by changing this value


    // Set initial pitch (if your game uses up/down looking)
    player->pitch = 0.0f; // Not needed for basic raycasting
}

// t_map *create_static_map(void)
// {
//     t_map* m = (t_map*)malloc(sizeof(t_map));
//     m->width = 29; // Width of the map
//     m->height = 19; // Height of the map
    
//     // Allocate memory for each row
//     m->tiles = (char**)malloc(m->height * sizeof(char*));
//     for(int i = 0; i < m->height; i++) {
//         m->tiles[i] = (char*)malloc((m->width + 1) * sizeof(char)); // +1 for null terminator
//         // Ensure the memory is allocated successfully
//         if (!m->tiles[i]) {
//             // Handle allocation failure (cleanup and error handling)
//         }
//     }
	
//     ft_strcpy(m->tiles[0], "11111111111111111111111111111");
//     ft_strcpy(m->tiles[1], "10000000001111000000000000001");
// 	ft_strcpy(m->tiles[2], "10110000011100000000000010001");
// 	ft_strcpy(m->tiles[3], "10010000000000000000000010001");
// 	ft_strcpy(m->tiles[4], "10110000011100000000000010001");
// 	ft_strcpy(m->tiles[5], "10000000001100000111011110001");
// 	ft_strcpy(m->tiles[6], "11110111111111011100000010001");
// 	ft_strcpy(m->tiles[7], "11110111111111011101010010001");
// 	ft_strcpy(m->tiles[8], "11000000110101011100000010001");
// 	ft_strcpy(m->tiles[9], "10000000000000001100000010001");
// 	ft_strcpy(m->tiles[10], "10000000000000001101010010001");
// 	ft_strcpy(m->tiles[11], "11000000110101000000000000001");
// 	ft_strcpy(m->tiles[12], "11110111110101000000000000001");
// 	ft_strcpy(m->tiles[13], "10000000001100000100000010001");
// 	ft_strcpy(m->tiles[14], "10000000000000001010000101001");
// 	ft_strcpy(m->tiles[15], "10000000001000010001010001001");
// 	ft_strcpy(m->tiles[16], "10000000001101000000N00000001");
// 	ft_strcpy(m->tiles[17], "10000000000100000001010000001");
// 	ft_strcpy(m->tiles[18], "11111111111111111111111111111");
	
    
//     return m;
// }

// t_map *create_static_map(void) {
//     t_map* map;
//     int i, j;
//     char *map_layout[] = {
//         "11111111111111111111111111111",
//         "10000000001111000000000000001",
//         "10110000011100000000000010001",
//         "10010000000000000000000010001",
//         "10110000011100000000000010001",
//         "10000000001100000111011110001",
//         "11110111111111011100000010001",
//         "11110111111111011101010010001",
//         "11000000110101011100000010001",
//         "10000000000000001100000010001",
//         "10000000000000001101010010001",
//         "11000000110101000000000000001",
//         "11110111110101000000000000001",
//         "10000000001100000100000010001",
//         "10000000000000001010000101001",
//         "10000000001000010001010001001",
//         "10000000001101000000N00000001",
//         "10000000000100000001010000001",
//         "11111111111111111111111111111"
//     };

//     map = (t_map*)malloc(sizeof(t_map));
//     map->width = 29;
//     map->height = 19;
//     map->tiles = (unsigned char**)malloc(map->height * sizeof(unsigned char*));

//     i = 0;
//     while (i < map->height) {
//         map->tiles[i] = (unsigned char*)malloc(map->width * sizeof(unsigned char));
//         j = 0;
//         while (j < map->width) {
//             map->tiles[i][j] = (unsigned char)map_layout[i][j];
//             j++;
//         }
//         i++;
//     }

//     return map;
// }


// unused
void initialize_game(t_game* game, int screen_width, int screen_height, char* title)
{
    // Initialize game components...

    game->map = create_static_map();
    // print_map(game->map); // Assuming print_map is adjusted to accept a pointer
		(void)screen_height;
	(void)screen_width;
	(void)title;
	(void)game;

// player
    game->player = malloc(sizeof(t_player));
    if (!game->player) {
        // Handle allocation failure (exit or error message)
        printf("Failed to allocate memory for player.\n");
        exit(1);
    }


    initialize_player(game->player);
    print_player(game->player);

}

// void initialize_game(t_game* game, int screen_width, int screen_height, char* title)
// {
// 	// MLX stuff
//     // Initialize MLX and create a window
//     // g->mlx_ptr = mlx_init();
//     // if (!g->mlx_ptr) {
//         // Handle error: MLX initialization failed
//         // exit(1);
//     // }

//     // g->win_ptr = mlx_new_window(g->mlx_ptr, screen_width, screen_height, title);
//     // if (!g->win_ptr) {
//         // Handle error: Window creation failed
//         // exit(1);
//     // }

//     // Create an image buffer for double buffering
//     // g->img_ptr = mlx_new_image(g->mlx_ptr, screen_width, screen_height);
//     // g->img_data = mlx_get_data_addr(g->img_ptr, &(g->bits_per_pixel), &(g->size_line), &(g->endian));

//     // Initialize additional game state (player, map, etc.) here
	

//     game->map = create_static_map();
// 	print_map(game->map);
// 	(void)screen_height;
// 	(void)screen_width;
// 	(void)title;
// 	(void)game;

// }


