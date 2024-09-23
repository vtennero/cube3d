/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures02_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitenner <vitenner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:13:26 by vitenner          #+#    #+#             */
/*   Updated: 2024/09/09 17:12:31 by vitenner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	gun_texture_frame_update(t_game *game, int frame, char *digits, char *path)
{
	digits[0] = '0' + (frame / 10);
	digits[1] = '0' + (frame % 10);
	game->gun_textures[frame - 1].img = mlx_xpm_file_to_image(game->mlx_ptr,
			path, &game->gun_textures[frame - 1].width,
			&game->gun_textures[frame - 1].height);
	if (game->gun_textures[frame - 1].img == NULL)
	{
		game->num_gun_frames = frame - 1;
		return (-1);
	}
	game->gun_textures[frame
		- 1].data = mlx_get_data_addr(game->gun_textures[frame - 1].img,
			&game->gun_textures[frame - 1].tex_bpp, &game->gun_textures[frame
			- 1].tex_line_len, &game->gun_textures[frame - 1].tex_endian);
	return (0);
}

int	load_gun_textures(t_game *game)
{
	char	path[24];
	char	*digits;
	int		frame;

	digits = &path[18];
	frame = 1;
	game->gun_textures = malloc(sizeof(t_texture) * MAX_GUN_TEXTURES);
	ft_strcpy(path, "textures/gun/frame00.xpm");
	while (frame <= MAX_GUN_TEXTURES)
	{
		upd_prog_bar(game, frame, MAX_GUN_TEXTURES,
			"Loading gun textures");
		if (gun_texture_frame_update(game, frame, digits, path) == -1)
			break ;
		frame++;
	}
	if (frame > MAX_GUN_TEXTURES)
		game->num_gun_frames = MAX_GUN_TEXTURES;
	return (0);
}

int	load_extract_textures(t_game *game)
{
	static char	*file_names[] = {"textures/extract/extract00.xpm",
		"textures/extract/extract01.xpm", "textures/extract/extract02.xpm",
		"textures/extract/extract03.xpm"};
	const int	num_textures = sizeof(file_names) / sizeof(file_names[0]);
	int			i;
	t_texture	*texture;

	i = 0;
	while (i < num_textures)
	{
		upd_prog_bar(game, i + 1, num_textures, \
		"Loading extract textures");
		texture = &game->extract_texture[i];
		texture->path = file_names[i];
		texture->img = mlx_xpm_file_to_image(game->mlx_ptr, texture->path,
				&texture->width, &texture->height);
		if (!texture->img)
			return (texture_err_message(game));
		texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp,
				&texture->tex_line_len, &texture->tex_endian);
		i++;
	}
	return (0);
}

int	load_floor_textures(t_game *game)
{
	char	path[26];
	int		f_digit;
	int		s_digit;
	int		texcount;

	ft_strcpy(path, "textures/floor/floor00.xpm");
	texcount = 0;
	get_last_two_digit_indexes(path, &f_digit, &s_digit);
	while (texcount < MAX_FLOOR_TEXTURES)
	{
		upd_prog_bar(game, texcount + 1, MAX_FLOOR_TEXTURES,
			"Loading floor textures");
		load_texture(game, &game->floortextures[texcount], path);
		texcount++;
		path[s_digit]++;
		if (path[s_digit] > '9')
		{
			path[s_digit] = '0';
			path[f_digit]++;
		}
	}
	return (0);
}

int	load_menu_texture(t_game *game)
{
	char		path[22];
	t_texture	*texture;

	texture = &game->menu_texture[0];
	ft_strcpy(path, "textures/menu/menu.xpm");
	texture->path = path;
	texture->img = mlx_xpm_file_to_image(game->mlx_ptr, path, &texture->width,
			&texture->height);
	if (!texture->img)
		return (texture_err_message(game));
	texture->data = mlx_get_data_addr(texture->img, &texture->tex_bpp,
			&texture->tex_line_len, &texture->tex_endian);
	return (0);
}
