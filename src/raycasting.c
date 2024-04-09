/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 18:49:22 by vitenner          #+#    #+#             */
/*   Updated: 2024/04/09 19:01:03 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void calculate_rays(t_game *game, int screenWidth) {
    t_ray rays[screenWidth]; // Array to store ray information
    double cameraX, rayDirX, rayDirY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpWallDist;
    int mapX, mapY;
    int stepX, stepY;
    int hit, side;
    int x;

    for (x = 0; x < screenWidth; x++) {
        cameraX = 2 * x / (double)screenWidth - 1; // x-coordinate in camera space
        rayDirX = game->player->direction.x + game->player->plane.x * cameraX;
        rayDirY = game->player->direction.y + game->player->plane.y * cameraX;

        mapX = (int)(game->player->position.x);
        mapY = (int)(game->player->position.y);

        deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        hit = 0; // Was there a wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (game->player->position.x - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - game->player->position.x) * deltaDistX;
        }
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (game->player->position.y - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - game->player->position.y) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0) {
            // Jump to next map square, OR in x-direction OR in y-direction
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            // Check if ray has hit a wall
            if (game->map->tiles[mapY][mapX] > 0) hit = 1;
        }

        // Calculate distance projected on camera direction
        if (side == 0) perpWallDist = (mapX - game->player->position.x + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - game->player->position.y + (1 - stepY) / 2) / rayDirY;

        // Save ray information
        rays[x].dir.x = rayDirX;
        rays[x].dir.y = rayDirY;
        rays[x].distance = perpWallDist;
        // Assume game->map->tiles uses positive numbers > 0 for walls and determines the type based on position
        rays[x].hitwalltype = (t_walltype)(game->map->tiles[mapY][mapX] - 1); // Simplification
    }

    // After all rays are calculated
    list_first_ten_rays(rays, screenWidth);
}

