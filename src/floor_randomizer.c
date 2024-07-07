/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_randomizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 19:44:02 by root              #+#    #+#             */
/*   Updated: 2024/07/07 19:54:35 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void initialize_floor_texture_weights(t_game *game)
{
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

unsigned long long xorshift64(unsigned long long *state)
{
    unsigned long long x = *state;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    *state = x;
    return x;
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
            printf("Assigned texture %d at position (%d, %d)\n", selected_texture, x, y);
        }
    }

    printf("initialize_floor_texture_map completed successfully\n");
}