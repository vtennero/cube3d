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

void	free_gun_texture_frames(t_game *game)
{
	int	i;

	if (!game->gun_textures)
		return ;
	i = 0;
	while (i < game->num_gun_frames)
	{
		destroy_texture(game, &game->gun_textures[i]);
		i++;
	}
	free(game->gun_textures);
	game->gun_textures = NULL;
}

void	free_shooting_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_SHOOTING_TEXTURES)
	{
		destroy_texture(game, &game->t_shoot[i]);
		i++;
	}
}

void	free_gun_textures(t_game *game)
{
	if (!game)
	{
		return ;
	}
	free_gun_texture_frames(game);
	free_shooting_textures(game);
}

void	free_texture_arrays(t_game *game)
{
	free_texture_array(game->walltextures, T_N_WALL, game);
	free_texture_array(game->floortextures, T_N_FLOOR, game);
	free_texture_array(game->enemy_textures, MAX_ENEMY_TEXTURES, game);
	free_texture_array(game->coll_texture, MAX_COLLECTIBLE_TEXTURES, game);
	free_texture_array(game->menu_texture, 1, game);
	free_texture_array(game->pelican_inside, 1, game);
	free_texture_array(game->t_intro2, T_N_INTRO2, game);
	free_texture_array(game->e_txt, 4, game);
	free_texture_array(game->supplies_texture, 1, game);
	free_texture_array(game->t_intro1, T_N_INTRO1, game);
	free_texture_array(game->t_outro, MAX_OUTRO_TEXTURES, game);
	free_texture_array(game->t_shoot, MAX_SHOOTING_TEXTURES, game);
	free_texture_array(game->t_eagle, NUM_AIRSTRIKE_FRAMES, game);
	free_texture_array(game->t_napalm, NUM_NAPALM_FRAMES, game);
	free_gun_textures(game);
	destroy_texture(game, &game->sky_texture);
	free_floor_texture_map(game);
	free_wall_texture_map_path(game);
}

void	cleanup(t_game *game)
{
	printf("Terminating...\n");
	clean_player(game);
	free_texture_arrays(game);
	clean_map(game);
	clean_rays(game);
	clean_mlx(game);
	cleanup_audio(game);
	free(game);
	exit(0);
}
