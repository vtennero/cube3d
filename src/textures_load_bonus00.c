/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures01_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:11:30 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 15:13:52 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int load_outro_textures(t_game *game)
{
	char path[27];
	int first_digit;
	int second_digit;
	int third_digit;
	int i;

	ft_strcpy(path, "textures/outro/outro000.xpm");
	get_last_three_digit_indexes(path, &first_digit, &second_digit, &third_digit);
	i = 0;
	while (i < MAX_OUTRO_TEXTURES)
	{
		path[first_digit] = '0' + (i / 100);
		path[second_digit] = '0' + ((i / 10) % 10);
		path[third_digit] = '0' + (i % 10);
		game->outro_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->outro_texture[i].width, &game->outro_texture[i].height);
		if (game->outro_texture[i].img == NULL)
			return (texture_err_message(game));
		game->outro_texture[i].data = mlx_get_data_addr(game->outro_texture[i].img, &game->outro_texture[i].tex_bpp, &game->outro_texture[i].tex_line_len, &game->outro_texture[i].tex_endian);
		update_progress_bar(game, i + 1, MAX_OUTRO_TEXTURES, "Loading outro textures");
		i++;
	}
	return (0);
}

int load_enemy_textures(t_game *game)
{
	char path[24];
	int first_digit;
	int second_digit;
	int third_digit;
	int i;

	ft_strcpy(path, "textures/enemies/000.xpm");
	get_last_three_digit_indexes(path, &first_digit, &second_digit, &third_digit);
	i = 0;
	while (i < NUM_ENEMY_TEXTURES)
	{
		path[first_digit] = '0' + (i / 100);
		path[second_digit] = '0' + ((i / 10) % 10);
		path[third_digit] = '0' + (i % 10);
		game->enemy_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->enemy_textures[i].width, &game->enemy_textures[i].height);
		if (game->enemy_textures[i].img == NULL)
			return (texture_err_message(game));
		game->enemy_textures[i].data = mlx_get_data_addr(game->enemy_textures[i].img, &game->enemy_textures[i].tex_bpp, &game->enemy_textures[i].tex_line_len, &game->enemy_textures[i].tex_endian);
		update_progress_bar(game, i + 1, MAX_ENEMY_TEXTURES, "Loading enemy textures");
		i++;
	}
	return (0);
}

int load_opening_textures(t_game *game)
{
	char path[29];
	int first_digit;
	int second_digit;
	int third_digit;
	int i;

	ft_strcpy(path, "textures/jump/xpm/jump000.xpm");
	get_last_three_digit_indexes(path, &first_digit, &second_digit, &third_digit);
	i = 0;
	while (i < MAX_OPENING_TEXTURES)
	{
		path[first_digit] = '0' + (i / 100);
		path[second_digit] = '0' + ((i / 10) % 10);
		path[third_digit] = '0' + (i % 10);
		game->opening_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->opening_texture[i].width, &game->opening_texture[i].height);
		if (game->opening_texture[i].img == NULL)
			return (texture_err_message(game));
		game->opening_texture[i].data = mlx_get_data_addr(game->opening_texture[i].img, &game->opening_texture[i].tex_bpp, &game->opening_texture[i].tex_line_len, &game->opening_texture[i].tex_endian);
		update_progress_bar(game, i + 1, MAX_OPENING_TEXTURES, "Loading opening textures");
		i++;
	}
	return (0);
}

int load_land_textures(t_game *game)
{
	char path[25];
	int first_digit;
	int second_digit;
	int third_digit;
	int i;

	ft_strcpy(path, "textures/land/land000.xpm");
	get_last_three_digit_indexes(path, &first_digit, &second_digit, &third_digit);
	i = 0;
	while (i < MAX_LAND_TEXTURES)
	{
		path[first_digit] = '0' + (i / 100);
		path[second_digit] = '0' + ((i / 10) % 10);
		path[third_digit] = '0' + (i % 10);
		game->land_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->land_texture[i].width, &game->land_texture[i].height);
		if (game->land_texture[i].img == NULL)
			return (texture_err_message(game));
		game->land_texture[i].data = mlx_get_data_addr(game->land_texture[i].img, &game->land_texture[i].tex_bpp, &game->land_texture[i].tex_line_len, &game->land_texture[i].tex_endian);
		update_progress_bar(game, i + 1, MAX_LAND_TEXTURES, "Loading land textures");
		i++;
	}
	return (0);
}

int load_collectible_texture(t_game *game)
{
	char path[39];

	update_progress_bar(game, 0, 1, "Loading collectible texture");
	ft_strcpy(path, "textures/collectibles/collectible01.xpm");
	game->coll_texture[0].img = mlx_xpm_file_to_image(game->mlx_ptr, (char *)path, &game->coll_texture[0].width, &game->coll_texture[0].height);
	if (!game->coll_texture[0].img)
		return (texture_err_message(game));
	game->coll_texture[0].data = mlx_get_data_addr(game->coll_texture[0].img, &game->coll_texture[0].tex_bpp, &game->coll_texture[0].tex_line_len, &game->coll_texture[0].tex_endian);
	update_progress_bar(game, 1, 1, "Loading collectible texture");
	return (0);
}
