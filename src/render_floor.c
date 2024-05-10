/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:41:48 by toto              #+#    #+#             */
/*   Updated: 2024/05/10 16:26:55 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

// Function to render the floor (lower half)
// void render_floor(t_img *img, int floor_color)
// {
//     int i, j;
//     for (i = DEFAULT_S_HEIGHT / 2; i < DEFAULT_S_HEIGHT; ++i) {
//         for (j = 0; j < DEFAULT_S_WIDTH; ++j) {
//             img_pix_put(img, j, i, floor_color);
//         }
//     }
// }

void render_floor(t_game *game)
{
	// printf("render floor\n");
    for (int y = DEFAULT_S_HEIGHT / 2; y < DEFAULT_S_HEIGHT; y++) {
        // Calculate initial ray directions for leftmost and rightmost rays
        float rayDirX0 = game->player->direction.x - game->player->plane.x;
        float rayDirY0 = game->player->direction.y - game->player->plane.y;
        float rayDirX1 = game->player->direction.x + game->player->plane.x;
        float rayDirY1 = game->player->direction.y + game->player->plane.y;

        // Perspective transformations
        int p = y - DEFAULT_S_HEIGHT / 2;
        float posZ = 0.5 * DEFAULT_S_HEIGHT;
        float rowDistance = posZ / p;

        // Step sizes for moving along the floor texture
        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

        // Starting position on the floor
        float floorX = game->player->position.x + rowDistance * rayDirX0;
        float floorY = game->player->position.y + rowDistance * rayDirY0;

        for (int x = 0; x < DEFAULT_S_WIDTH; ++x) {
            // Calculate the cell coordinates on the floor
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            // Calculate texture coordinates
            int tx = (int)(game->floortexture[0].width * (floorX - cellX)) & (game->floortexture[0].width - 1);
            int ty = (int)(game->floortexture[0].height * (floorY - cellY)) & (game->floortexture[0].height - 1);

            // Advance the floor texture coordinates
            floorX += floorStepX;
            floorY += floorStepY;

            // Retrieve the texture color and plot the pixel
            int color = get_texture_color(&game->floortexture[0], tx, ty);
        	// printf("render_floor: calling img_pix_put\n");
            img_pix_put(&game->img, x, y, color);
        }
    }
}

