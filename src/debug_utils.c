/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:08:24 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/09 18:51:35 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void print_map(t_map* map)
{
    if (map == NULL || map->tiles == NULL) {
        printf("Map data is not initialized.\n");
        return;
    }

    for (int y = 0; y < map->height; y++) {
        for (int x = 0; x < map->width; x++) {
            // Print each tile; '1' for walls and '0' for spaces are printed directly.
            // Adjust printing characters as needed for different elements.
            printf("%c ", map->tiles[y][x]);
        }
        printf("\n"); // New line after each row
    }
}

void list_first_ten_rays(t_ray *rays, int count)
{
    int limit = (count < 10) ? count : 10; // Ensure we don't go out of bounds if less than 10 rays
    for (int i = 0; i < limit; i++) {
        printf("Ray %d: Distance = %f, Wall Type = %d\n",
               i, rays[i].distance, rays[i].hitwalltype);
    }
}
