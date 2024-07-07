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
        fprintf(stderr, "Error: Texture index out of bounds: %d\n", index);
        return 0;
    }

    return *(int *)(texture->data + index);
}

// void render_floor(t_game *game)
// {
// 	// printf("render floor\n");
//     for (int y = DEFAULT_S_HEIGHT / 2; y < DEFAULT_S_HEIGHT; y++) {
//         // Calculate initial ray directions for leftmost and rightmost rays
//         float rayDirX0 = game->player->direction.x - game->player->plane.x;
//         float rayDirY0 = game->player->direction.y - game->player->plane.y;
//         float rayDirX1 = game->player->direction.x + game->player->plane.x;
//         float rayDirY1 = game->player->direction.y + game->player->plane.y;

//         // Perspective transformations
//         int p = y - DEFAULT_S_HEIGHT / 2;
//         float posZ = 0.5 * DEFAULT_S_HEIGHT;
//         float rowDistance = posZ / p;

//         // Step sizes for moving along the floor texture
//         float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
//         float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

//         // Starting position on the floor
//         float floorX = game->player->position.x + rowDistance * rayDirX0;
//         float floorY = game->player->position.y + rowDistance * rayDirY0;

//         for (int x = 0; x < DEFAULT_S_WIDTH; ++x) {
//             // Calculate the cell coordinates on the floor
//             int cellX = (int)(floorX);
//             int cellY = (int)(floorY);

//             // Calculate texture coordinates
//             int tx = (int)(game->floortextures[0].width * (floorX - cellX)) & (game->floortextures[0].width - 1);
//             int ty = (int)(game->floortextures[0].height * (floorY - cellY)) & (game->floortextures[0].height - 1);

//             // Advance the floor texture coordinates
//             floorX += floorStepX;
//             floorY += floorStepY;

//             // Retrieve the texture color and plot the pixel
//             int color = get_texture_color(&game->floortextures[0], tx, ty);
//         	// printf("render_floor: calling img_pix_put\n");
//             img_pix_put(&game->img, x, y, color);
//         }
//     }
// }

// this works and is stable, for 1 texture as of july 8
// void render_floor(t_game *game)
// {
//     for (int y = DEFAULT_S_HEIGHT / 2; y < DEFAULT_S_HEIGHT; y++)
//     {
//         // Calculate initial ray directions for leftmost and rightmost rays
//         float rayDirX0 = game->player->direction.x - game->player->plane.x;
//         float rayDirY0 = game->player->direction.y - game->player->plane.y;
//         float rayDirX1 = game->player->direction.x + game->player->plane.x;
//         float rayDirY1 = game->player->direction.y + game->player->plane.y;

//         // Perspective transformations
//         int p = y - DEFAULT_S_HEIGHT / 2;
//         float posZ = 0.5 * DEFAULT_S_HEIGHT;
//         float rowDistance = posZ / p;

//         // Step sizes for moving along the floor texture
//         float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
//         float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

//         // Starting position on the floor
//         float floorX = game->player->position.x + rowDistance * rayDirX0;
//         float floorY = game->player->position.y + rowDistance * rayDirY0;

//         for (int x = 0; x < DEFAULT_S_WIDTH; ++x)
//         {
//             // Calculate the cell coordinates on the floor
//             int cellX = (int)(floorX);
//             int cellY = (int)(floorY);

//             // Calculate texture coordinates
//             float fracX = floorX - cellX;
//             float fracY = floorY - cellY;
//             int tx = (int)(fracX * game->floortextures[0].width);
//             int ty = (int)(fracY * game->floortextures[0].height);

//             // Ensure tx and ty are within bounds
//             tx = (tx < 0) ? 0 : (tx >= game->floortextures[0].width) ? game->floortextures[0].width - 1
//                                                                      : tx;
//             ty = (ty < 0) ? 0 : (ty >= game->floortextures[0].height) ? game->floortextures[0].height - 1
//                                                                       : ty;

//             // Advance the floor texture coordinates
//             floorX += floorStepX;
//             floorY += floorStepY;

//             // Retrieve the texture color and plot the pixel
//             int color = get_texture_color(&game->floortextures[0], tx, ty);
//             img_pix_put(&game->img, x, y, color);
//         }
//     }
// }

// void initialize_floor_texture_weights(t_game *game)
// {
//     float weights[] = {0.20, 0.20, 0.20, 0.20, 0.05, 0.05, 0.05, 0.05};
//     game->num_floor_textures = MAX_FLOOR_TEXTURES;

//     for (int i = 0; i < game->num_floor_textures; i++)
//     {
//         game->floor_texture_weights[i].weight = weights[i];
//         game->floor_texture_weights[i].texture_index = i;
//     }
//     printf("initialize_floor_texture_weights completed\n");
// }

// int select_weighted_texture(t_game *game)
// {
//     float random = (float)random_int(game, 10000) / 10000.0f;
//     float cumulative = 0;
//     for (int i = 0; i < game->num_floor_textures; i++)
//     {
//         cumulative += game->floor_texture_weights[i].weight;
//         if (random <= cumulative)
//         {
//             return i;
//         }
//     }
//     return 0;
// }

// void initialize_floor_texture_map(t_game *game)
// {
//     game->floor_texture_map = malloc(game->map->height * sizeof(int *));
//     for (int y = 0; y < game->map->height; y++)
//     {
//         game->floor_texture_map[y] = malloc(game->map->width * sizeof(int));
//         for (int x = 0; x < game->map->width; x++)
//         {
//             game->random_seed += (unsigned long long)x * 31 + (unsigned long long)y * 17;
//             game->floor_texture_map[y][x] = select_weighted_texture(game);
//             printf("initialize floor texture map %d\n", game->floor_texture_map[y][x]);
//         }
//     }
//     printf("initialize_floor_texture_map completed\n");
// }

// int get_texture_color(t_texture *texture, int x, int y)
// {
//     if (!texture || !texture->data)
//     {
//         // printf("Texture or texture data is NULL\n");
//         return 0;
//     }

//     if (x < 0 || x >= TEXTURE_SIZE || y < 0 || y >= TEXTURE_SIZE)
//     {
//         // printf("Texture coordinates out of bounds in get_texture_color\n");
//         return 0;
//     }

//     int pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);

//     if (pixel_pos < 0 || pixel_pos >= texture->tex_line_len * TEXTURE_SIZE)
//     {
//         // printf("Pixel position out of bounds in get_texture_color\n");
//         return 0;
//     }

//     return *(int *)(texture->data + pixel_pos);
// }

int get_texture_color(t_texture *texture, int x, int y)
{
    // printf("Getting texture color at (X: %d, Y: %d)\n", x, y);
    int pixel_pos = y * texture->tex_line_len + x * (texture->tex_bpp / 8);
    int color = *(int *)(texture->data + pixel_pos);
    return color;
}

void render_floor(t_game *game)
{
    if (!game || !game->player || !game->map || !game->floor_texture_map)
    {
        fprintf(stderr, "Error: Invalid game state in render_floor\n");
        return;
    }

    // printf("Starting render_floor. Map dimensions: %d x %d\n", game->map->width, game->map->height);

    for (int y = DEFAULT_S_HEIGHT / 2; y < DEFAULT_S_HEIGHT; y++)
    {
        float rayDirX0 = game->player->direction.x - game->player->plane.x;
        float rayDirY0 = game->player->direction.y - game->player->plane.y;
        float rayDirX1 = game->player->direction.x + game->player->plane.x;
        float rayDirY1 = game->player->direction.y + game->player->plane.y;

        int p = y - DEFAULT_S_HEIGHT / 2;
        float posZ = 0.5 * DEFAULT_S_HEIGHT;
        float rowDistance = posZ / p;

        float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / DEFAULT_S_WIDTH;
        float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / DEFAULT_S_WIDTH;

        float floorX = game->player->position.x + rowDistance * rayDirX0;
        float floorY = game->player->position.y + rowDistance * rayDirY0;

        for (int x = 0; x < DEFAULT_S_WIDTH; ++x)
        {
            int cellX = (int)(floorX);
            int cellY = (int)(floorY);

            if (cellX < 0 || cellX >= game->map->width || cellY < 0 || cellY >= game->map->height)
            {
                // printf("Out of bounds: cellX=%d, cellY=%d\n", cellX, cellY);
                floorX += floorStepX;
                floorY += floorStepY;
                continue;
            }

            int texture_index = game->floor_texture_map[cellY][cellX];

            if (texture_index < 0 || texture_index >= MAX_FLOOR_TEXTURES)
            {
                printf("Invalid texture index: %d at cellX=%d, cellY=%d\n", texture_index, cellX, cellY);
                floorX += floorStepX;
                floorY += floorStepY;
                continue;
            }

            t_texture *current_texture = &game->floortextures[texture_index];
            // printf("render floor: x= %d textureindex is %d\n", x, texture_index);
            if (!current_texture || !current_texture->data)
            {
                printf("Invalid texture at index: %d\n", texture_index);
                floorX += floorStepX;
                floorY += floorStepY;
                continue;
            }

            float fracX = floorX - cellX;
            float fracY = floorY - cellY;
            int tx = (int)(fracX * current_texture->width);
            int ty = (int)(fracY * current_texture->height);

            int color = get_floor_texture_color(current_texture, tx, ty);
            img_pix_put(&game->img, x, y, color);

            floorX += floorStepX;
            floorY += floorStepY;
        }
    }

    // printf("Finished render_floor\n");
}

// void render_floor_pixel(t_game *game, int x, int y, float floorX, float floorY)
// {
//     int cellX = (int)floorX;
//     int cellY = (int)floorY;

//     // Ensure we're within map bounds
//     if (cellX < 0 || cellX >= game->map->width || cellY < 0 || cellY >= game->map->height)
//     {
//         return;
//     }

//     int texture_index = game->floor_texture_map[cellY][cellX];

//     // Ensure texture index is valid
//     if (texture_index < 0 || texture_index >= MAX_FLOOR_TEXTURES)
//     {
//         return;
//     }

//     t_texture *current_texture = &game->floortextures[texture_index];

//     // Calculate texture coordinates with higher precision
//     float tx = (floorX - cellX) * TEXTURE_SIZE;
//     float ty = (floorY - cellY) * TEXTURE_SIZE;

//     // Use bilinear interpolation for smoother texture sampling
//     int x1 = (int)tx & (TEXTURE_SIZE - 1);
//     int y1 = (int)ty & (TEXTURE_SIZE - 1);
//     int x2 = (x1 + 1) & (TEXTURE_SIZE - 1);
//     int y2 = (y1 + 1) & (TEXTURE_SIZE - 1);

//     float fracX = tx - (int)tx;
//     float fracY = ty - (int)ty;

//     int c1 = get_texture_color(current_texture, x1, y1);
//     int c2 = get_texture_color(current_texture, x2, y1);
//     int c3 = get_texture_color(current_texture, x1, y2);
//     int c4 = get_texture_color(current_texture, x2, y2);

//     // Bilinear interpolation
//     int r = (1 - fracX) * (1 - fracY) * ((c1 >> 16) & 0xFF) +
//             fracX * (1 - fracY) * ((c2 >> 16) & 0xFF) +
//             (1 - fracX) * fracY * ((c3 >> 16) & 0xFF) +
//             fracX * fracY * ((c4 >> 16) & 0xFF);

//     int g = (1 - fracX) * (1 - fracY) * ((c1 >> 8) & 0xFF) +
//             fracX * (1 - fracY) * ((c2 >> 8) & 0xFF) +
//             (1 - fracX) * fracY * ((c3 >> 8) & 0xFF) +
//             fracX * fracY * ((c4 >> 8) & 0xFF);

//     int b = (1 - fracX) * (1 - fracY) * (c1 & 0xFF) +
//             fracX * (1 - fracY) * (c2 & 0xFF) +
//             (1 - fracX) * fracY * (c3 & 0xFF) +
//             fracX * fracY * (c4 & 0xFF);

//     int color = (r << 16) | (g << 8) | b;

//     // Put pixel on screen
//     img_pix_put(&game->img, x, y, color);
// }

// void render_floor_pixel(t_game *game, int x, int y, float floorX, float floorY)
// {
//     int cellX = (int)floorX;
//     int cellY = (int)floorY;

//     // Use cellX and cellY to determine texture index
//     int texture_index = (cellX + cellY) % MAX_FLOOR_TEXTURES;

//     t_texture *current_texture = &game->floortextures[texture_index];

//     float fracX = floorX - cellX;
//     float fracY = floorY - cellY;
//     int tx = (int)(fracX * current_texture->width) & (current_texture->width - 1);
//     int ty = (int)(fracY * current_texture->height) & (current_texture->height - 1);

//     int color = get_floor_texture_color(current_texture, tx, ty);
//     img_pix_put(&game->img, x, y, color);
// }

void render_floor_pixel(t_game *game, int x, int y, float floorX, float floorY)
{
    int cellX = (int)floorX;
    int cellY = (int)floorY;

    // Ensure we're within map bounds
    if (cellX >= 0 && cellX < game->map->width && cellY >= 0 && cellY < game->map->height)
    {
        int texture_index = game->floor_texture_map[cellY][cellX];

        // Check if the texture index is valid
        if (texture_index >= 0 && texture_index < MAX_FLOOR_TEXTURES)
        {
            t_texture *current_texture = &game->floortextures[texture_index];

            float fracX = floorX - cellX;
            float fracY = floorY - cellY;
            int tx = (int)(fracX * current_texture->width) % current_texture->width;
            int ty = (int)(fracY * current_texture->height) % current_texture->height;

            int color = get_floor_texture_color(current_texture, tx, ty);
            img_pix_put(&game->img, x, y, color);
        }
        else
        {
            fprintf(stderr, "Invalid texture index: %d at cellX=%d, cellY=%d\n", texture_index, cellX, cellY);
            // Use a default color (e.g., red) for invalid texture indices
            img_pix_put(&game->img, x, y, 0xFF0000);
        }
    }
    else
    {
        // Use a default color (e.g., blue) for out-of-bounds coordinates
        img_pix_put(&game->img, x, y, 0x0000FF);
    }
}