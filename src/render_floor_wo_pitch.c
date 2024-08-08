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

            // if (tx < 0 || ty < 0 || tx >= current_texture->width || ty >= current_texture->height) {
            //     printf("Suspicious texture coordinates: tx=%d, ty=%d, texture size=%dx%d\n",
            //            tx, ty, current_texture->width, current_texture->height);
            //     printf("fracX=%f, fracY=%f, floorX=%f, floorY=%f\n", fracX, fracY, floorX, floorY);
            // }
            int color = get_floor_texture_color(current_texture, tx, ty);
            img_pix_put(&game->img, x, y, color);

            floorX += floorStepX;
            floorY += floorStepY;
        }
    }

    // printf("Finished render_floor\n");
}

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