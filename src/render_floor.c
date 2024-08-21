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
#define FIXED_POINT_FACTOR 256
#define MAX_DISTANCE 1000000.0f 

int get_floor_texture_color(t_texture *texture, int x, int y)
{
    if (!texture || !texture->data)
    {
        fprintf(stderr, "Error: Invalid texture in get_floor_texture_color\n");
        return 0;
    }

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
    {
        // fprintf(stderr, "Error: Texture coordinates out of bounds: x=%d, y=%d, texture size=%dx%d\n",
        // x, y, texture->width, texture->height);
        return 0;
    }

    int index = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
    if (index < 0 || index >= texture->tex_line_len * texture->height)
    {
        // debug_texture(texture, x, y);
        fprintf(stderr, "Error: Texture index out of bounds: %d\n", index);
        return 0;
    }

    return *(int *)(texture->data + index);
}

void initialize_floor_texture_weights(t_game *game)
{
    // float weights[] = {0.5, 0, 0, 0, 0, 0, 0.5, 0};
    float weights[] = {0.20, 0.20, 0.20, 0.20, 0.05, 0.05, 0.05, 0.05};
    game->num_floor_textures = MAX_FLOOR_TEXTURES;

    float total_weight = 0;
    for (int i = 0; i < game->num_floor_textures; i++)
    {
        total_weight += weights[i];
    }

    for (int i = 0; i < game->num_floor_textures; i++)
    {
        game->floor_texture_weights[i].weight = weights[i] / total_weight;
        game->floor_texture_weights[i].texture_index = i;
        printf("Texture %d weight: %.4f\n", i, game->floor_texture_weights[i].weight);
    }
    printf("initialize_floor_texture_weights completed\n");
}

int select_weighted_texture(t_game *game)
{
    if (game->num_floor_textures <= 0)
    {
        fprintf(stderr, "Error: No floor textures available\n");
        return 0;
    }

    double random = (double)rand() / RAND_MAX;
    double cumulative = 0;
    for (int i = 0; i < game->num_floor_textures; i++)
    {
        cumulative += game->floor_texture_weights[i].weight;
        if (random <= cumulative)
        {
            return i;
        }
    }
    return 0; // Fallback to first texture if something goes wrong
}

void initialize_floor_texture_map(t_game *game)
{
    printf("Entering initialize_floor_texture_map\n");
    printf("Map dimensions: width=%d, height=%d\n", game->map->width, game->map->height);

    if (game->floor_texture_map != NULL)
    {
        printf("floor_texture_map is already allocated. Freeing existing memory.\n");
        for (int y = 0; y < game->map->height; y++)
        {
            free(game->floor_texture_map[y]);
        }
        free(game->floor_texture_map);
    }

    game->floor_texture_map = malloc(game->map->height * sizeof(int *));
    if (game->floor_texture_map == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for floor_texture_map\n");
        exit(EXIT_FAILURE);
    }

    for (int y = 0; y < game->map->height; y++)
    {
        game->floor_texture_map[y] = malloc(game->map->width * sizeof(int));
        if (game->floor_texture_map[y] == NULL)
        {
            fprintf(stderr, "Failed to allocate memory for floor_texture_map row %d\n", y);
            // Free previously allocated rows
            for (int i = 0; i < y; i++)
            {
                free(game->floor_texture_map[i]);
            }
            free(game->floor_texture_map);
            exit(EXIT_FAILURE);
        }

        for (int x = 0; x < game->map->width; x++)
        {
            int selected_texture = select_weighted_texture(game);
            game->floor_texture_map[y][x] = selected_texture;
            // printf("Assigned texture %d at position (%d, %d)\n", selected_texture, x, y);
        }
    }

    printf("initialize_floor_texture_map completed successfully\n");
}


void render_floor_pixel(t_game *game, int x, int y, float floorX, float floorY)
{
    int cellX = (int)floorX;
    int cellY = (int)floorY;

    if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
    {
        int texture_index = game->floor_texture_map[cellY][cellX];

        if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
        {
            t_texture *current_texture = &game->floortextures[texture_index];

            float fracX = floorX - cellX;
            float fracY = floorY - cellY;
            
            // Use fmodf to ensure we're always within texture bounds
            int tx = (int)(fmodf(fracX * current_texture->width, current_texture->width));
            int ty = (int)(fmodf(fracY * current_texture->height, current_texture->height));

            // Ensure tx and ty are always non-negative
            tx = (tx + current_texture->width) % current_texture->width;
            ty = (ty + current_texture->height) % current_texture->height;

            int color = get_floor_texture_color(current_texture, tx, ty);
            img_pix_put(&game->img, x, y, color);
        }
        else
        {
            img_pix_put(&game->img, x, y, 0xFF0000); // Red for invalid texture index
        }
    }
    else
    {
        img_pix_put(&game->img, x, y, 0x0000FF); // Blue for out-of-bounds
    }
}

// this one works with player height of 0

// void render_floor(t_game *game)
// {
//     if (!game || !game->player || !game->map || !game->floor_texture_map)
//     {
//         fprintf(stderr, "Error: Invalid game state in render_floor\n");
//         return;
//     }

//     float pitch = game->player->pitch;
//     int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
//     int height_offset = 0;

//     int horizon = DEFAULT_S_HEIGHT / 2;
//     int floor_start = horizon - pitch_pixel_offset + height_offset;
//     floor_start = (floor_start < 0) ? 0 : (floor_start >= DEFAULT_S_HEIGHT ? DEFAULT_S_HEIGHT - 1 : floor_start);

//     for (int y = floor_start; y < DEFAULT_S_HEIGHT; y++)
//     {
//         float rayDirX0 = game->player->direction.x - game->player->plane.x;
//         float rayDirY0 = game->player->direction.y - game->player->plane.y;
//         float rayDirX1 = game->player->direction.x + game->player->plane.x;
//         float rayDirY1 = game->player->direction.y + game->player->plane.y;

//         int p = y - (horizon - pitch_pixel_offset + height_offset);
//         float posZ = 0.5f * DEFAULT_S_HEIGHT;

//         float rowDistance = p > 0 ? posZ / p : MAX_DISTANCE;

//         float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
//         float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

//         float floorX = game->player->position.x + rowDistance * rayDirX0;
//         float floorY = game->player->position.y + rowDistance * rayDirY0;

//         for (int x = 0; x < DEFAULT_S_WIDTH; x++)
//         {
//             int cellX = (int)floorX;
//             int cellY = (int)floorY;

//             if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
//             {
//                 int texture_index = game->floor_texture_map[cellY][cellX];

//                 if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
//                 {
//                     t_texture *current_texture = &game->floortextures[texture_index];

//                     if (current_texture && current_texture->data)
//                     {
//                         float fracX = floorX - floorf(floorX);
//                         float fracY = floorY - floorf(floorY);
//                         float tx = fracX * current_texture->width;
//                         float ty = fracY * current_texture->height;
                        
//                         // Ensure tx and ty are always within texture bounds
//                         tx = fmodf(tx, current_texture->width);
//                         ty = fmodf(ty, current_texture->height);
                        
//                         if (tx < 0) tx += current_texture->width;
//                         if (ty < 0) ty += current_texture->height;

//                         int color = get_floor_texture_color(current_texture, (int)tx, (int)ty);
//                         img_pix_put(&game->img, x, y, color);
//                     }
//                 }
//             }
//             floorX += floorStepX;
//             floorY += floorStepY;
//         }
//     }
// }
void render_floor(t_game *game)
{
    if (!game || !game->player || !game->map || !game->floor_texture_map)
    {
        fprintf(stderr, "Error: Invalid game state in render_floor\n");
        return;
    }

    float pitch = game->player->pitch;
    int pitch_pixel_offset = -(int)(pitch * DEFAULT_S_HEIGHT);
    float player_height = game->player->height;  // Use player's height

    int horizon = DEFAULT_S_HEIGHT / 2;
    int floor_start = horizon - pitch_pixel_offset;
    floor_start = (floor_start < 0) ? 0 : (floor_start >= DEFAULT_S_HEIGHT ? DEFAULT_S_HEIGHT - 1 : floor_start);

    for (int y = floor_start; y < DEFAULT_S_HEIGHT; y++)
    {
        float rayDirX0 = game->player->direction.x - game->player->plane.x;
        float rayDirY0 = game->player->direction.y - game->player->plane.y;
        float rayDirX1 = game->player->direction.x + game->player->plane.x;
        float rayDirY1 = game->player->direction.y + game->player->plane.y;

        int p = y - horizon + pitch_pixel_offset;
        float posZ = 0.5f * DEFAULT_S_HEIGHT * (1.0f + player_height*2);  // Adjust for player height

        float rowDistance = posZ / p;

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

        float floorX = game->player->position.x + rowDistance * rayDirX0;
        float floorY = game->player->position.y + rowDistance * rayDirY0;

        for (int x = 0; x < DEFAULT_S_WIDTH; x++)
        {
            int cellX = (int)floorX;
            int cellY = (int)floorY;

            if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
            {
                int texture_index = game->floor_texture_map[cellY][cellX];

                if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
                {
                    t_texture *current_texture = &game->floortextures[texture_index];

                    if (current_texture && current_texture->data)
                    {
                        float fracX = floorX - floorf(floorX);
                        float fracY = floorY - floorf(floorY);
                        float tx = fracX * current_texture->width;
                        float ty = fracY * current_texture->height;
                        
                        // Ensure tx and ty are always within texture bounds
                        tx = fmodf(tx, current_texture->width);
                        ty = fmodf(ty, current_texture->height);
                        
                        if (tx < 0) tx += current_texture->width;
                        if (ty < 0) ty += current_texture->height;

                        int color = get_floor_texture_color(current_texture, (int)tx, (int)ty);
                        img_pix_put(&game->img, x, y, color);
                    }
                }
            }
            floorX += floorStepX;
            floorY += floorStepY;
        }
    }
}