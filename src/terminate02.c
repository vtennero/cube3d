/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:00:21 by toto              #+#    #+#             */
/*   Updated: 2024/08/27 16:42:05 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"


void	clean_player(t_game *game)
{
    printf("clean_player\n");
	free(game->player);
	game->player = NULL;
    printf("clean_player DONE\n");
}

void clean_mlx(t_game *game)
{
    printf("clean_mlx\n");
    if (game->img.mlx_img)
        mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
    
    if (game->win_ptr)
        mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    
    if (game->mlx_ptr)
    {
        mlx_destroy_display(game->mlx_ptr);
        free(game->mlx_ptr);
    }
    printf("clean_mlx DONE\n");

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
    printf("clean_textures\n");
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
    printf("clean_textures DONE\n");
}





// void free_map(t_game *game) {
//     if (game->map != NULL) {
//         if (game-map->data != NULL) {
//             // Free each row
//             for (int i = 0; i < game->screen_height; i++) {
//                 free(map->data[i]);
//             }
//             // Free the array of rows
//             free(map->data);
//         }
//         // Free the map structure
//         free(map);
//     }
// }



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


// void cleanup_strike_textures(t_game *game)
// {
//     for (int i = 0; i < NUM_AIRSTRIKE_FRAMES; i++)
//     {
//         if (game->airstrike_textures[i].img)
//             mlx_destroy_image(game->mlx_ptr, game->airstrike_textures[i].img);
//     }
//     free(game->airstrike_textures);
// }

// void free_texture_array(t_texture *textures, int num_items, t_game*game)
// {
//     printf("free_texture_array %d items\n", num_items);
//     for (int i = 0; i < num_items; i++)
//     {
//         if (textures[i].img != NULL)
//         {
//             mlx_destroy_image(game->mlx_ptr, textures[i].img);  // Free the image resource
//             textures[i].img = NULL;  // Set the pointer to NULL to avoid dangling pointers
//         }
//     }
//     printf("free_texture_array DONE\n");
// }

void free_texture_array(t_texture *texture_array, int num_items, t_game *game)
{
    int i;

    printf("free_texture_array\n");
    if (!game || !texture_array)
        return;

    for (i = 0; i < num_items; i++)
    {
        // if (texture_array[i].path)
        // {
        //     free(texture_array[i].path);
        //     texture_array[i].path = NULL;
        // }
        if (texture_array[i].img)
        {
            mlx_destroy_image(game->mlx_ptr, texture_array[i].img);
            texture_array[i].img = NULL;
        }
        // Note: We don't free texture_array[i].data separately because 
        // it's typically managed by MLX and freed by mlx_destroy_image
    }
    printf("free_texture_array DONE\n");
}

void free_gun_textures(t_game *game)
{
    int i;

    if (!game)
        return;

    // Free regular gun textures
    if (game->gun_textures)
    {
        for (i = 0; i < game->num_gun_frames; i++)
        {
            if (game->gun_textures[i].path)
            {
                free(game->gun_textures[i].path);
                game->gun_textures[i].path = NULL;
            }
            if (game->gun_textures[i].img)
            {
                mlx_destroy_image(game->mlx_ptr, game->gun_textures[i].img);
                game->gun_textures[i].img = NULL;
            }
        }
        free(game->gun_textures);
        game->gun_textures = NULL;
    }

    // Free shooting textures
    for (i = 0; i < MAX_SHOOTING_TEXTURES; i++)
    {
        if (game->shooting_texture[i].path)
        {
            free(game->shooting_texture[i].path);
            game->shooting_texture[i].path = NULL;
        }
        if (game->shooting_texture[i].img)
        {
            mlx_destroy_image(game->mlx_ptr, game->shooting_texture[i].img);
            game->shooting_texture[i].img = NULL;
        }
    }

    game->num_gun_frames = 0;
    game->current_gun_frame = 0;
    game->current_shooting_frame = 0;
}

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

void	cleanup(t_game *game)
{
	printf("cleanup\n");
	clean_player(game);
	// clean_textures(game);
	// clean_floor();


    free_texture_array(game->walltextures,MAX_WALL_TEXTURES,game);
    free_texture_array(game->floortextures,MAX_FLOOR_TEXTURES,game);
    free_texture_array(game->skytexture,MAX_SKY_TEXTURES,game);
    free_texture_array(game->enemy_textures,MAX_ENEMY_TEXTURES,game);
    free_texture_array(game->coll_texture,MAX_COLLECTIBLE_TEXTURES,game);
    free_texture_array(game->menu_texture,1,game);
    // free_texture_array(game->pelican_inside,1,game);

    free_texture_array(game->land_texture,MAX_LAND_TEXTURES,game);

    free_texture_array(game->extract_texture,4,game);
    free_texture_array(game->supplies_texture,1,game);
    free_texture_array(game->opening_texture,MAX_OPENING_TEXTURES,game);

    free_texture_array(game->outro_texture,MAX_OUTRO_TEXTURES,game);
    free_texture_array(game->shooting_texture,MAX_SHOOTING_TEXTURES,game);
    free_texture_array(game->airstrike_textures,NUM_AIRSTRIKE_FRAMES,game);
    free_gun_textures(game);
    free_floor_texture_map(game);
	free_wall_texture_map_path(game);
    // free(game->strike);
	clean_map(game);
//	free_map(game->map);
	freeArray(game->cub_map_array,game->cub_map_row_count);
	clean_rays(game);
	clean_mlx(game);
    cleanupAudio();
	free(game);







	exit(0);
}


