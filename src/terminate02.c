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
	free(game->player);
	game->player = NULL;
}

void clean_mlx(t_game *game)
{
	if (game->img.mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);

	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);

	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}
void	clean_rays(t_game *game)
{
	struct s_ray_node *current;
	struct s_ray_node *next;
	int ray_count = 0;

	if (game == NULL)
	{
		printf("Error: game pointer is NULL\n");
		return;
	}

	current = game->ray_list;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
		ray_count++;
	}

	game->ray_list = NULL;
}


void destroy_texture_in_array(t_game *game, t_texture *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(game->mlx_ptr, texture->img);
		texture->img = NULL;
	}
}

void free_texture_array(t_texture *texture_array, int num_items, t_game *game)
{
	int i;

	if (!game || !texture_array)
		return;

	for (i = 0; i < num_items; i++)
		destroy_texture_in_array(game, &texture_array[i]);
}

void destroy_texture(t_game *game, t_texture *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(game->mlx_ptr, texture->img);
		texture->img = NULL;
	}
}

void free_gun_texture_frames(t_game *game)
{
	int i;

	if (!game->gun_textures)
		return;
	for (i = 0; i < game->num_gun_frames; i++)
		destroy_texture(game, &game->gun_textures[i]);
	free(game->gun_textures);
	game->gun_textures = NULL;
}

void free_shooting_textures(t_game *game)
{
	int i;

	for (i = 0; i < MAX_SHOOTING_TEXTURES; i++)
		destroy_texture(game, &game->shooting_texture[i]);
}

void reset_gun_frames(t_game *game)
{
	game->num_gun_frames = 0;
	game->current_gun_frame = 0;
	game->current_shooting_frame = 0;
}
void free_sky_texture(t_game *game)
{
	destroy_texture_in_array(game, &game->sky_texture);
}
void free_gun_textures(t_game *game)
{
	if (!game)
		return;
	free_gun_texture_frames(game);
	free_shooting_textures(game);
	reset_gun_frames(game);
}
void	free_texture_arrays(t_game *game)
{
	free_texture_array(game->walltextures,MAX_WALL_TEXTURES,game);
	free_texture_array(game->floortextures,MAX_FLOOR_TEXTURES,game);
	free_texture_array(game->enemy_textures,MAX_ENEMY_TEXTURES,game);
	free_texture_array(game->coll_texture,MAX_COLLECTIBLE_TEXTURES,game);
	free_texture_array(game->menu_texture,1,game);
	free_texture_array(game->pelican_inside,1,game);
	free_texture_array(game->land_texture,MAX_LAND_TEXTURES,game);
	free_texture_array(game->extract_texture,4,game);
	free_texture_array(game->supplies_texture,1,game);
	free_texture_array(game->opening_texture,MAX_OPENING_TEXTURES,game);
	free_texture_array(game->outro_texture,MAX_OUTRO_TEXTURES,game);
	free_texture_array(game->shooting_texture,MAX_SHOOTING_TEXTURES,game);
	free_texture_array(game->airstrike_textures,NUM_AIRSTRIKE_FRAMES,game);
	free_texture_array(game->napalm_textures,NUM_NAPALM_FRAMES,game);
	free_gun_textures(game);
	free_sky_texture(game);
	free_floor_texture_map(game);
	free_wall_texture_map_path(game);
}

void	cleanup(t_game *game)
{
	printf("cleanup\n");
	clean_player(game);
	free_texture_arrays(game);
	// free(game->strike);
	clean_map(game);
	clean_rays(game);
	clean_mlx(game);
	cleanup_audio(game);
	free(game);
	exit(0);
}


