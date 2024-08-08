/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:19:19 by root              #+#    #+#             */
/*   Updated: 2024/07/09 18:19:19 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void print_vector2d(const t_vector2d *vector)
{
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
    if (game == NULL || game->map == NULL)
    {
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
    for (int y = 24 - 1; y >= 0; y--)
    {
        for (int x = 0; x < 24; x++)
        {
            if (y == playerY && x == playerX)
            {
                printf("X ");
            }
            else
            {
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
    while (temp != NULL)
    {
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
    while (temp != NULL && idx < first_count)
    {
        printf("Ray %d: x = %d, cameraX = %f, rayDirX = %f, rayDirY = %f\n",
               idx, temp->ray.x, temp->ray.cameraX, temp->ray.rayDirX, temp->ray.rayDirY);
        // Add more properties as needed
        temp = temp->next;
        idx++;
    }

    // Skip intermediate rays if the total count is greater than 20
    int skip_count = count - (first_count + last_count);
    while (skip_count-- > 0 && temp != NULL)
    {
        temp = temp->next;
    }

    // Print the last `last_count` rays
    printf("\nLast %d rays:\n", last_count);
    idx = count - last_count;
    while (temp != NULL && idx < count)
    {
        printf("Ray %d: x = %d, cameraX = %f, rayDirX = %f, rayDirY = %f\n",
               idx, temp->ray.x, temp->ray.cameraX, temp->ray.rayDirX, temp->ray.rayDirY);
        // Add more properties as needed
        temp = temp->next;
        idx++;
    }
}

void debug_texture(t_texture *texture, int x, int y)
{
    if (!texture)
    {
        printf("Error: Texture pointer is NULL\n");
        return;
    }

    printf("-------------------:\n");
    printf("Debugging t_texture:\n");
    // printf("Path: %s\n", texture->path ? texture->path : "no path");
    printf("Image pointer: %p\n", (void*)texture->img);
    printf("Data pointer: %p\n", (void*)texture->data);
    printf("Width: %d\n", texture->width);
    printf("Height: %d\n", texture->height);
    printf("Bits per pixel: %d\n", texture->tex_bpp);
    printf("Line length: %d\n", texture->tex_line_len);
    printf("Endian: %d\n", texture->tex_endian);
    printf("Requested coordinates: x=%d, y=%d\n", x, y);
}

void print_ray(const t_ray *ray)
{
	printf("print_ray\n");
	printf("x: %d\n", ray->x);
	printf("cameraX: %.2f\n", ray->cameraX);
	printf("rayDirX: %.2f\n", ray->rayDirX);
	printf("rayDirY: %.2f\n", ray->rayDirY);
	printf("mapX: %d\n", ray->mapX);
	printf("mapY: %d\n", ray->mapY);
	printf("sideDistX: %.2f\n", ray->sideDistX);
	printf("sideDistY: %.2f\n", ray->sideDistY);
	printf("deltaDistX: %.2f\n", ray->deltaDistX);
	printf("deltaDistY: %.2f\n", ray->deltaDistY);
	printf("perpWallDist: %.2f\n", ray->perpWallDist);
	printf("stepX: %d\n", ray->stepX);
	printf("stepY: %d\n", ray->stepY);
	printf("hit: %d\n", ray->hit);
	printf("side: %d\n", ray->side);
	printf("lineHeight: %d\n", ray->lineHeight);
	printf("draw_start: %d\n", ray->draw_start);
	printf("draw_end: %d\n", ray->draw_end);
	printf("color: %d\n", ray->color);
	printf("wall_face: %d\n", ray->wall_face);
	printf("******************************\n");
}