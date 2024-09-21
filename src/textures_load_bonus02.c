/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_load_bonus02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cliew <cliew@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:03:04 by cliew             #+#    #+#             */
/*   Updated: 2024/09/21 18:03:04 by cliew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	load_pelican_inside_texture(t_game *game)
{
	char		path[34];
	t_texture	*texture;

	ft_printf("Loading ship texture\t\t\t[#");
	ft_strcpy(path, "textures/extract/pelicaninside.xpm");
	texture = &game->pelican_inside[0];
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (texture_err_message(game));
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp,
			&texture->tex_line_len, &texture->tex_endian);
	ft_printf("#############################] 100.0%%\n");
	return (0);
}

int	load_supplies_texture(t_game *game)
{
	char		path[30];
	t_texture	*texture;

	printf("Loading supplies texture\t\t[#");
	ft_strcpy(path, "textures/supplies/supplies.xpm");
	texture = &game->supplies_texture[0];
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (texture_err_message(game));
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp,
			&texture->tex_line_len, &texture->tex_endian);
	printf("#############################] 100.0%%\n");
	return (0);
}

int	load_strike_textures(t_game *game)
{
	char	path[22];
	int		first_digit;
	int		second_digit;
	int		i;

	ft_strcpy(path, "textures/strike/00.xpm");
	get_last_two_digit_indexes(path, &first_digit, &second_digit);
	i = 0;
	while (i < NUM_AIRSTRIKE_FRAMES)
	{
		path[first_digit] = '0' + (i / 10);
		path[second_digit] = '0' + (i % 10);
		game->as_txture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path,
				&game->as_txture[i].width, &game->as_txture[i].height);
		if (game->as_txture[i].img == NULL)
			return (texture_err_message(game));
		game->as_txture[i].data = mlx_get_data_addr(game->as_txture[i].img,
				&game->as_txture[i].tex_bpp, &game->as_txture[i].tex_line_len,
				&game->as_txture[i].tex_endian);
		update_progress_bar(game, i + 1, NUM_AIRSTRIKE_FRAMES,
			"Loading strike textures");
		i++;
	}
	return (0);
}

int	load_napalm_textures(t_game *game)
{
	char	path[28];
	int		first_digit;
	int		second_digit;
	int		i;

	ft_strcpy(path, "textures/strike/napalm00.xpm");
	get_last_two_digit_indexes(path, &first_digit, &second_digit);
	i = 0;
	while (i < NUM_NAPALM_FRAMES)
	{
		path[first_digit] = '0' + (i / 10);
		path[second_digit] = '0' + (i % 10);
		game->np_txture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path,
				&game->np_txture[i].width, &game->np_txture[i].height);
		if (game->np_txture[i].img == NULL)
			return (texture_err_message(game));
		game->np_txture[i].data = mlx_get_data_addr(game->np_txture[i].img,
				&game->np_txture[i].tex_bpp, &game->np_txture[i].tex_line_len,
				&game->np_txture[i].tex_endian);
		update_progress_bar(game, i + 1, NUM_NAPALM_FRAMES,
			"Loading napalm textures");
		i++;
	}
	return (0);
}

int	load_shooting_textures(t_game *game)
{
	char	path[33];
	int		first_digit;
	int		second_digit;
	int		i;

	ft_strcpy(path, "textures/gun/shooting/frame00.xpm");
	get_last_two_digit_indexes(path, &first_digit, &second_digit);
	i = 0;
	while (i < MAX_SHOOTING_TEXTURES)
	{
		path[first_digit] = '0' + (i / 10);
		path[second_digit] = '0' + (i % 10);
		game->sht_txture[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path,
				&game->sht_txture[i].width, &game->sht_txture[i].height);
		if (game->sht_txture[i].img == NULL)
			return (texture_err_message(game));
		game->sht_txture[i].data = mlx_get_data_addr(game->sht_txture[i].img,
				&game->sht_txture[i].tex_bpp, &game->sht_txture[i].tex_line_len,
				&game->sht_txture[i].tex_endian);
		update_progress_bar(game, i + 1, MAX_SHOOTING_TEXTURES,
			"Loading shooting textures");
		i++;
	}
	return (0);
}
