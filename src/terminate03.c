/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:21:05 by cliew             #+#    #+#             */
/*   Updated: 2024/08/27 15:28:23 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube3d.h"


void free_split_result(char **words) {
    if (words == NULL) {
        return;  // Handle case where words is NULL
    }

    for (int i = 0; words[i] != NULL; i++) {
        free(words[i]);  // Free each string
    }

    free(words);  // Free the array of pointers
}

void freeArray(int **array, int x) {
    int i = 0;

    // Free each inner array
    while (i < x) {
        free(array[i]);
        i++;
    }

    // Free the outer array
    free(array);
}


void free_floor_texture_map(t_game *game)
{
    if (!game || !game->floor_texture_map || !game->map)
        return;

    for (int y = 0; y < game->map->height; y++)
    {
        if (game->floor_texture_map[y])
        {
            free(game->floor_texture_map[y]);
            game->floor_texture_map[y] = NULL;
        }
    }

    free(game->floor_texture_map);
    game->floor_texture_map = NULL;
}


void free_wall_texture_map_path(t_game *game)
{

	free(game->walltextures[0].path);
	free(game->walltextures[1].path);
	free(game->walltextures[2].path);
	free(game->walltextures[3].path);
	free(game->floor_rgb[0].path);
	free(game->sky_rgb[0].path);
}

void clean_map(t_game *game)
{
    printf("clean_map\n");
    if (game && game->map)
    {
        // Free the 2D array of map data
        if (game->map->data)
        {
            for (int i = 0; i < game->map->height; i++)
            {
                if (game->map->data[i])
                {
                    free(game->map->data[i]);
                }
            }
            free(game->map->data);
            game->map->data = NULL;
        }

        // Free the map structure itself
        free(game->map);
        game->map = NULL;
    }
    printf("clean_map DONE\n");
}
