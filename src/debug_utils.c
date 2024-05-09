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

// void print_game_map(t_game *game)
// {
//     if (game == NULL || game->map == NULL) {
//         printf("Game or game map is not initialized.\n");
//         return;
//     }

//     t_map *map = game->map;
//     printf("Map dimensions: %dx%d\n", 24, 24);
//     // printf("Map dimensions: %dx%d\n", map->width, map->height);

//     // Get the player's position in integer coordinates using floor
//     int playerX = floor(game->player->position.x);
//     int playerY = floor(game->player->position.y);

//     printf("Map dimensions: %dx%d\n", map->width, map->height);
//     printf("Player position (floored): %d, %d\n", playerX, playerY);

//     for (int y = 0; y < 24; y++) {
//         for (int x = 0; x < 24; x++) {
//             if (y == playerY && x == playerX) {
//                 printf("X ");
//             } else {
//                 printf("%d ", map->data[y][x]);
//             }
//         }
//         printf("\n");
//     }
// }


void print_game_map(t_game *game)
{
    if (game == NULL || game->map == NULL) {
        printf("Game or game map is not initialized.\n");
        return;
    }

    t_map *map = game->map;
    printf("Map dimensions: %dx%d\n", 24, 24);

    // Get the player's position in integer coordinates using floor
    int playerX = floor(game->player->position.x);
    int playerY = floor(game->player->position.y);

    printf("Player position (floored): %d, %d\n", playerX, playerY);

    // Iterate from the bottom to the top for y
    for (int y = 24 - 1; y >= 0; y--) {
        for (int x = 0; x < 24; x++) {
            if (y == playerY && x == playerX) {
                printf("X ");
            } else {
                printf("%d ", map->data[y][x]);
            }
        }
        printf("\n");
    }
}

void debug_print_rays(t_ray_node *head)
{
    // Step 1: Calculate the length of the linked list
    int count = 0;
    t_ray_node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    // Step 2: Print the first 10 and last 10 rays if possible
    int first_count = (count < 10) ? count : 10;
    int last_count = (count < 20) ? (count - first_count) : 10;
    int idx = 0;

    temp = head;

    // Print the first `first_count` rays
    printf("First %d rays:\n", first_count);
    while (temp != NULL && idx < first_count) {
        printf("Ray %d: x = %d, cameraX = %f, rayDirX = %f, rayDirY = %f\n",
               idx, temp->ray.x, temp->ray.cameraX, temp->ray.rayDirX, temp->ray.rayDirY);
        // Add more properties as needed
        temp = temp->next;
        idx++;
    }

    // Skip intermediate rays if the total count is greater than 20
    int skip_count = count - (first_count + last_count);
    while (skip_count-- > 0 && temp != NULL) {
        temp = temp->next;
    }

    // Print the last `last_count` rays
    printf("\nLast %d rays:\n", last_count);
    idx = count - last_count;
    while (temp != NULL && idx < count) {
        printf("Ray %d: x = %d, cameraX = %f, rayDirX = %f, rayDirY = %f\n",
               idx, temp->ray.x, temp->ray.cameraX, temp->ray.rayDirX, temp->ray.rayDirY);
        // Add more properties as needed
        temp = temp->next;
        idx++;
    }
}