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
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
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
	texture->data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
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
		game->t_eagle[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path,
				&game->t_eagle[i].width, &game->t_eagle[i].height);
		if (game->t_eagle[i].img == NULL)
			return (texture_err_message(game));
		game->t_eagle[i].data = mlx_get_data_addr(game->t_eagle[i].img,
				&game->t_eagle[i].bpp, &game->t_eagle[i].line_len,
				&game->t_eagle[i].endian);
		upd_prog_bar(game, i + 1, NUM_AIRSTRIKE_FRAMES,
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
		game->t_napalm[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path,
				&game->t_napalm[i].width, &game->t_napalm[i].height);
		if (game->t_napalm[i].img == NULL)
			return (texture_err_message(game));
		game->t_napalm[i].data = mlx_get_data_addr(game->t_napalm[i].img,
				&game->t_napalm[i].bpp, &game->t_napalm[i].line_len,
				&game->t_napalm[i].endian);
		upd_prog_bar(game, i + 1, NUM_NAPALM_FRAMES,
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
		game->t_shoot[i].img = mlx_xpm_file_to_image(game->mlx_ptr, path,
				&game->t_shoot[i].width, &game->t_shoot[i].height);
		if (game->t_shoot[i].img == NULL)
			return (texture_err_message(game));
		game->t_shoot[i].data = mlx_get_data_addr(game->t_shoot[i].img,
				&game->t_shoot[i].bpp, &game->t_shoot[i].line_len,
				&game->t_shoot[i].endian);
		upd_prog_bar(game, i + 1, MAX_SHOOTING_TEXTURES,
			"Loading shooting textures");
		i++;
	}
	return (0);
}
