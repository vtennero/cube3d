/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures03_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:29 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 17:14:05 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int load_pelican_inside_texture(t_game *game)
{
	char path[34];
	t_texture *texture;

	ft_printf("Loading ship texture\t\t\t[#");
	ft_strcpy(path, "textures/extract/pelicaninside.xpm");
	texture = &game->pelican_inside[0];
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
		return (texture_err_message(game));
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
	printf("#############################] 100.0%%\n");
	return (0);
}

int load_supplies_texture(t_game *game)
{
	char path[30];
	t_texture *texture;

	printf("Loading supplies texture\t\t[#");
	ft_strcpy(path, "textures/supplies/supplies.xpm");
	texture = &game->supplies_texture[0];
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width, &texture->height);
	if (!texture->img)
		return (texture_err_message(game));
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp, &texture->tex_line_len, &texture->tex_endian);
	printf("#############################] 100.0%%\n");
	return (0);
}

int load_strike_textures(t_game *game)
{
	char path[22];
	int first_digit;
	int second_digit;
	int i;

	ft_strcpy(path, "textures/strike/00.xpm");
	get_last_two_digit_indexes(path, &first_digit, &second_digit);
	i = 0;
	while (i < NUM_AIRSTRIKE_FRAMES)
	{
		path[first_digit] = '0' + (i / 10);
		path[second_digit] = '0' + (i % 10);
		game->airstrike_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->airstrike_textures[i].width, &game->airstrike_textures[i].height);
		if (game->airstrike_textures[i].img == NULL)
			return (texture_err_message(game));
		game->airstrike_textures[i].data = mlx_get_data_addr(game->airstrike_textures[i].img, &game->airstrike_textures[i].tex_bpp, &game->airstrike_textures[i].tex_line_len, &game->airstrike_textures[i].tex_endian);
		update_progress_bar(game, i + 1, NUM_AIRSTRIKE_FRAMES, "Loading strike textures");
		i++;
	}
	return (0);
}

int load_napalm_textures(t_game *game)
{
	char path[28];
	int first_digit;
	int second_digit;
	int i;

	ft_strcpy(path, "textures/strike/napalm00.xpm");
	get_last_two_digit_indexes(path, &first_digit, &second_digit);
	i = 0;
	while (i < NUM_NAPALM_FRAMES)
	{
		path[first_digit] = '0' + (i / 10);
		path[second_digit] = '0' + (i % 10);
		game->napalm_textures[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->napalm_textures[i].width, &game->napalm_textures[i].height);
		if (game->napalm_textures[i].img == NULL)
			return (texture_err_message(game));
		game->napalm_textures[i].data = mlx_get_data_addr(game->napalm_textures[i].img, &game->napalm_textures[i].tex_bpp, &game->napalm_textures[i].tex_line_len, &game->napalm_textures[i].tex_endian);
		update_progress_bar(game, i + 1, NUM_NAPALM_FRAMES, "Loading napalm textures");
		i++;
	}
	return (0);
}

int load_shooting_textures(t_game *game)
{
	char path[33];
	int first_digit;
	int second_digit;
	int i;

	ft_strcpy(path, "textures/gun/shooting/frame00.xpm");
	get_last_two_digit_indexes(path, &first_digit, &second_digit);
	i = 0;
	while (i < MAX_SHOOTING_TEXTURES)
	{
		path[first_digit] = '0' + (i / 10);
		path[second_digit] = '0' + (i % 10);
		game->shooting_texture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path, &game->shooting_texture[i].width, &game->shooting_texture[i].height);
		if (game->shooting_texture[i].img == NULL)
			return (texture_err_message(game));
		game->shooting_texture[i].data = mlx_get_data_addr(game->shooting_texture[i].img, &game->shooting_texture[i].tex_bpp, &game->shooting_texture[i].tex_line_len, &game->shooting_texture[i].tex_endian);
		update_progress_bar(game, i + 1, MAX_SHOOTING_TEXTURES, "Loading shooting textures");
		i++;
	}
	return (0);
}
