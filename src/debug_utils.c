/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:08:24 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/15 12:18:42 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// void print_map(t_map* map)
// {
// 	if (map == NULL || map->tiles == NULL) {
// 		printf("Map data is not initialized.\n");
// 		return;
// 	}

// 	for (int y = 0; y < map->height; y++) {
// 		for (int x = 0; x < map->width; x++) {
// 			// Print each tile; '1' for walls and '0' for spaces are printed directly.
// 			// Adjust printing characters as needed for different elements.
// 			printf("%c ", map->tiles[y][x]);
// 		}
// 		printf("\n"); // New line after each row
// 	}
// }

// void print_map(t_map* map) {
//     int y, x;
//     unsigned char tile;
    
//     if (map == NULL || map->tiles == NULL) {
//         printf("Map data is not initialized.\n");
//         return;
//     }

//     y = 0;
//     while (y < map->height) {
//         x = 0;
//         while (x < map->width) {
//             tile = map->tiles[y][x];
//             if (tile == TILE_SPACE) {
//                 printf("0 ");
//             } else if (tile == TILE_WALL) {
//                 printf("1 ");
//             } else {
//                 printf("%c ", tile); // For player and potentially other special tiles
//             }
//             x++;
//         }
//         printf("\n"); // New line after each row
//         y++;
//     }
// }


void print_vector2d(const t_vector2d *vector) {
    const char *format;

    format = "Vector2D(x: %.2f, y: %.2f)\n";

    printf(format, vector->x, vector->y);
}


void print_player(const t_player *player)
{
    const char *format_position_direction, *format_plane_pitch;

    format_position_direction = "Player(Position: (%.2f, %.2f), Direction: (%.2f, %.2f))\n";
    format_plane_pitch = "Plane: (%.2f, %.2f), Pitch: %.2f\n";

    printf(format_position_direction, player->position.x, player->position.y, player->direction.x, player->direction.y);
    printf(format_plane_pitch, player->plane.x, player->plane.y, player->pitch);
}

void print_game_map(t_game *game)
{
    if (game == NULL || game->map == NULL) {
        printf("Game or game map is not initialized.\n");
        return;
    }

    t_map *map = game->map;
    printf("Map dimensions: %dx%d\n", 24, 24);
    // printf("Map dimensions: %dx%d\n", map->width, map->height);

    // Get the player's position in integer coordinates using floor
    int playerX = floor(game->player->position.x);
    int playerY = floor(game->player->position.y);

    printf("Map dimensions: %dx%d\n", map->width, map->height);
    printf("Player position (floored): %d, %d\n", playerX, playerY);

    for (int y = 0; y < 24; y++) {
        for (int x = 0; x < 24; x++) {
            if (y == playerY && x == playerX) {
                printf("X "); // Print emoji for player's position
            } else {
                printf("%d ", map->data[y][x]);
            }
        }
        printf("\n");
    }
}

