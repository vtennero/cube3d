/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:29:32 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:29:32 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void load_wall_textures(t_game *game)
{
	for (int i = NORTH; i <= WEST; i++)
	{
		game->walltextures[i].img = mlx_xpm_file_to_image(
			game->mlx_ptr,
			game->walltextures[i].path,
			&game->walltextures[i].width,
			&game->walltextures[i].height);

		if (!game->walltextures[i].img)
		{
			fprintf(stderr, "Failed to load wall texture: %s\n", game->walltextures[i].path);
			exit(EXIT_FAILURE);
		}

		game->walltextures[i].data = mlx_get_data_addr(
			game->walltextures[i].img,
			&game->walltextures[i].tex_bpp,
			&game->walltextures[i].tex_line_len,
			&game->walltextures[i].tex_endian);

		printf("Loaded wall texture: %s, bpp: %d, size: %dx%d\n",
			   game->walltextures[i].path, game->walltextures[i].tex_bpp,
			   game->walltextures[i].width, game->walltextures[i].height);
	}

	printf("load_wall_textures END\n");
}

void	load_bonus_textures(t_game *game)
{
	load_floor_textures(game);
	load_collectible_texture(game, "textures/collectibles/collectible01.xpm");
	load_gun_textures(game);
	load_shooting_textures(game);
	// load_gun_textures(game, "textures/gun/frame%02d.xpm", 12);
	// load_shooting_textures(game, "textures/gun/shooting/frame%02d.xpm", MAX_SHOOTING_TEXTURES);
	load_enemy_textures(game, "textures/enemies/%03d.xpm", NUM_ENEMY_TEXTURES);
	load_menu_texture(game, "textures/menu/menu.xpm");
	load_opening_textures(game, "textures/jump/xpm/jump%03d.xpm", MAX_OPENING_TEXTURES);
	load_land_textures(game, "textures/land/land%03d.xpm", MAX_LAND_TEXTURES);
	load_outro_textures(game, "textures/outro/outro%03d.xpm", MAX_OUTRO_TEXTURES);
	load_extract_textures(game);
	load_napalm_textures(game);
	load_strike_textures(game);
	load_supplies_texture(game, "textures/supplies/supplies.xpm");
	load_pelican_inside_texture(game, "textures/extract/pelicaninside.xpm");
	scale_gun_textures(game);
	scale_shooting_textures(game);
}

void	load_textures(t_game *game)
{
	load_wall_textures(game);
	if (game->bonus == 1)
		load_bonus_textures(game);
}
