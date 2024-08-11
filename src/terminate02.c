/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toto <toto@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:00:21 by toto              #+#    #+#             */
/*   Updated: 2024/08/11 19:34:05 by toto             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	clean_player(t_game *game)
{
	free(game->player);
	game->player = NULL;
}

void	clean_mlx(t_game *game)
{
    mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
    mlx_destroy_display(game->mlx_ptr);
    free(game->mlx_ptr);
}
void clean_texture(t_texture *textures, int num_textures)
{
    int i;
	printf("cleaning %d textures\n", num_textures);
    for (i = 0; i < num_textures; i++)
    {
        if (textures[i].path)
            free(textures[i].path);
        if (textures[i].img)
            free(textures[i].img);
        if (textures[i].data)
            free(textures[i].data);
        
        // Reset all members to ensure clean state
        textures[i].path = NULL;
        textures[i].img = NULL;
        textures[i].data = NULL;
        textures[i].width = 0;
        textures[i].height = 0;
        textures[i].tex_bpp = 0;
        textures[i].tex_line_len = 0;
        textures[i].tex_endian = 0;
    }
}

void clean_textures(t_game *game)
{
    clean_texture(game->walltextures, MAX_WALL_TEXTURES);
    clean_texture(game->floortextures, MAX_FLOOR_TEXTURES);
    clean_texture(game->skytexture, MAX_SKY_TEXTURES);
    clean_texture(game->enemy_textures, MAX_ENEMY_TEXTURES);
    clean_texture(game->coll_texture, MAX_COLLECTIBLE_TEXTURES);

    // Handle gun textures separately as they're dynamically allocated
    if (game->gun_textures)
    {
        clean_texture(game->gun_textures, game->num_gun_frames);
        free(game->gun_textures);
        game->gun_textures = NULL;
        game->num_gun_frames = 0;
        game->current_gun_frame = 0;
    }
}
void clean_map(t_game *game)
{
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
}


// void	clean_floor(t_game *game)
// 	int					**floor_texture_map;


void	clean_rays(t_game *game)
{
    struct s_ray_node *current;
    struct s_ray_node *next;
    int ray_count = 0;

    // printf("Starting to free ray list\n");
    
    if (game == NULL)
    {
        printf("Error: game pointer is NULL\n");
        return;
    }

    current = game->ray_list;
    while (current != NULL)
    {
        // printf("About to free ray %d at address %p\n", ray_count, (void*)current);
        next = current->next;
        free(current);
        // printf("Freed ray %d\n", ray_count);
        current = next;
        ray_count++;
    }

    game->ray_list = NULL;
    // printf("Finished freeing ray list. Total rays freed: %d\n", ray_count);
}


// void	clean_(t_game *game)
// void	clean_(t_game *game)
// void	clean_(t_game *game)
// void	clean_(t_game *game)
// void	clean_(t_game *game)

void	cleanup(t_game *game)
{
	printf("cleanup\n");
	clean_player(game);
	// clean_mlx();
	// clean_textures(game);
	clean_map(game);
	// clean_floor();
	clean_rays(game);
	free(game);







	exit(0);
}