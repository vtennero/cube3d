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

int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(
		game->mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_putstr_fd("Failed to load texture: ", 2);
		ft_putendl_fd(path, 2);
		return (0);
	}
	texture->data = mlx_get_data_addr(texture->img,
			&texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
	return (1);
}


int	load_wall_textures(t_game *game)
{
	int	i;
	int	total_textures;
	int	err_check;

	i = NORTH;
	err_check = 0;
	total_textures = WEST - NORTH + 1;
	while (i <= WEST)
	{
		err_check = load_texture(game, &game->walltextures[i], game->walltextures[i].path);
		if (err_check == 0)
			return (texture_err_message(game));
		update_progress_bar(game, i - NORTH + 1, total_textures, "Loading wall textures");
		i++;
	}
	return (0);
}


void	load_bonus_textures(t_game *game)
{
	load_floor_textures(game);
	load_sky_texture(game);
	load_collectible_texture(game);
	load_gun_textures(game);
	load_shooting_textures(game);
	load_enemy_textures(game);
	load_menu_texture(game);
	load_opening_textures(game);
	load_land_textures(game);
	load_outro_textures(game);
	load_extract_textures(game);
	load_napalm_textures(game);
	load_strike_textures(game);
	load_supplies_texture(game);
	load_pelican_inside_texture(game);
	scale_gun_textures(game);
	scale_shooting_textures(game);
}

void	load_textures(t_game *game)
{
	game->text_err = load_wall_textures(game);
	if (game->bonus == 1)
		load_bonus_textures(game);
	if (game->text_err > 0)
	{
		printf("Error: Failed to load %d texture sets\n", game->text_err);
		cleanup(game);
		return ;
	}
}
